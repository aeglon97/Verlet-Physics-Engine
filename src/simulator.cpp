#include "simulator.h"
#include "stick.h"
#include <random>
#include <memory>

//Initialize window and renderer in initializer list
Simulator::Simulator(const int screenWidth, const int screenHeight) :
        _screenWidth(screenWidth),
        _screenHeight(screenHeight)
{
    srand((unsigned int)time(NULL));

    _window = InitializeWindow();
    _renderer = InitializeRenderer();
    

    //Initialize cloth
    InitializeCloth(10, 10);

    
    InitializeDots(4);
    _dots[0]->SetPosition(100, 100);
    _dots[1]->SetPosition(200, 100);
    _dots[2]->SetPosition(200, 200);
    _dots[3]->SetPosition(100, 200);
    _dots[0]->Pin(true);


    _sticks.push_back(new Stick(_dots[0], _dots[1]));
    _sticks.push_back(new Stick(_dots[1], _dots[2]));
    _sticks.push_back(new Stick(_dots[2], _dots[3]));
    _sticks.push_back(new Stick(_dots[0], _dots[3]));
    _sticks.push_back(new Stick(_dots[0], _dots[2]));
    _sticks[4]->Hide(true);

}

//Initialize cloth
void Simulator::InitializeCloth(const int height, const int width)
{
    _cloth = new Cloth(10, 10);
    _cloth->setWindow(_window);
    _cloth->setRenderer(_renderer);
    _cloth->InitializeDots();
}

//Create vector of dots, passed to initializer list
void Simulator::InitializeDots(const int n)
{
    std::vector<Dot*> dots;
    for (int i = 0; i < n; ++i)
    {
        Dot *dot = new Dot(10);
        dot->setWindow(_window);
        dot->setRenderer(_renderer);
        _dots.push_back(dot);
    }
}

//Create window to pass to initializer list
SDL_Window* Simulator::InitializeWindow()
{
    SDL_Window* window = SDL_CreateWindow("Verlet Physics Engine",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _screenWidth, _screenHeight, 0);

    return window;
}

//Create renderer to pass to initializer list
SDL_Renderer* Simulator::InitializeRenderer()
{
    SDL_Renderer* renderer = SDL_CreateRenderer(_window,-1, SDL_RENDERER_ACCELERATED);

    return renderer;
}

//Infinite while loop checking game state
void Simulator::Loop()
{
    bool running = true;
    while(running)
    {
        //Handle events
        while(SDL_PollEvent(&_windowEvent) != 0)
        {
            //Handle user input
            switch(_windowEvent.type)
            {
                case SDL_QUIT:
                running = false;
                break;
            }

            //Clear all current sprites, render 10-15 new objects with spacebar
        }
        
        //Account for frame rate
        this->Update(1.0/60.0);
        this->Draw();
    }
}

//Motion/logic handler
void Simulator::Update(double deltaTime)
{   
    //Update points
    for (Dot* dot : _dots) { dot->Update(deltaTime); }

    //Add point rigidity
    for(int i = 0; i < 5; ++i)
    {
        //Update structures
        
        //Update sticks
        for (Stick *stick : _sticks) { stick->Update(); }
        // Constrain points
        for (Dot* dot : _dots) { dot->ApplyConstraints(); }
    }
    // _cloth->Update(deltaTime);
    
}

//Refresh current frame
void Simulator::Draw()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    //Draw dots
    for (Dot* dot : _dots) { dot->Draw(); }

    //Draw sticks
    for (Stick* stick : _sticks) { stick->Draw(); }

    //Draw structures
    // _cloth->Draw();

    //Render to screen
    SDL_RenderPresent(_renderer);
}

//Destructor
Simulator::~Simulator()
{
    SDL_DestroyWindow(_window);

    //Deallocate dots in vector
    for(Dot* dot : _dots) { delete dot; }

    //Deallocate sticks
    for(Stick* stick : _sticks) { delete stick; }

    delete _cloth;
}


