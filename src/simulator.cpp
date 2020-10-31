#include "simulator.h"
#include "stick.h"
#include "engine.h"
#include <random>
#include <memory>

//Initialize window and renderer in initializer list
Simulator::Simulator(const int screenWidth, const int screenHeight) :
        _screenWidth(screenWidth),
        _screenHeight(screenHeight)
{
    srand((unsigned int)time(NULL));

    InitializeWindow();
    InitializeRenderer();
    

    //Initialize cloth
    InitializeCloth(20, 20);

    // InitializeDots(4);
    // _dots[0]->SetPosition(100, 100);
    // _dots[1]->SetPosition(200, 100);
    // _dots[2]->SetPosition(200, 200);
    // _dots[3]->SetPosition(100, 200);
    // _dots[0]->Pin(true);

    InitializePoints(4);
    _points[0]->setPosition(100, 100);
    _points[1]->setPosition(200, 200);
    // std::cout << _points[0]->getX() << _points[0]->getY() << std::endl;
    // std::cout << _points[1]->getX() << _points[1]->getY() << std::endl;


    _engine = new Engine();
    std::cout << _engine->getFriction() << std::endl;

    
    


    // _sticks.push_back(new Stick(_dots[0], _dots[1]));
    // _sticks.push_back(new Stick(_dots[1], _dots[2]));
    // _sticks.push_back(new Stick(_dots[2], _dots[3]));
    // _sticks.push_back(new Stick(_dots[0], _dots[3]));
    // _sticks.push_back(new Stick(_dots[0], _dots[2]));
    // _sticks[4]->Hide(true);

}

//Initialize cloth
void Simulator::InitializeCloth(const int height, const int width)
{
    _cloth = new Cloth(height, width);
    _cloth->setWindow(_window);
    _cloth->setRenderer(_renderer);
    _cloth->CreateMatrix(0);
    std::cout << "Created matrix" << std::endl;
}

//Create points
void Simulator::InitializePoints(const int n)
{
    for (int i = 0; i < n; ++i)
    {
        Point* point = new Point(2, 2);
        point->setWindow(_window);
        point->setRenderer(_renderer);
        _points.push_back(point);
    }
}

//Create vector of dots, passed to initializer list
//TODO: Repurpose Dots to be Balls
void Simulator::InitializeDots(const int n)
{
    for (int i = 0; i < n; ++i)
    {
        Dot *dot = new Dot(1);
        dot->setWindow(_window);
        dot->setRenderer(_renderer);
        dot->AssignTexture("../img/dot.png");
        _dots.push_back(dot);
    }
}

//Create window to pass to initializer list
void Simulator::InitializeWindow()
{
    _window = SDL_CreateWindow("Verlet Physics Engine",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _screenWidth, _screenHeight, 0);
}

//Create renderer to pass to initializer list
void Simulator::InitializeRenderer()
{
    _renderer = SDL_CreateRenderer(_window,-1, SDL_RENDERER_ACCELERATED);

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

            for(auto &vec : _cloth->getMatrix()){
                for(auto &dot : vec)
                {
                    dot->HandleEvents(_windowEvent);
                }
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
        // for (Dot* dot : _dots) { dot->ApplyConstraints(); }
    }
    
    _cloth->Update(deltaTime);

    for (Point* point : _points)
    {
        point->Update(deltaTime);
        // std::cout << point->getX() << point->getY() << std::endl;
        // std::cout << point->getY() << std::endl;
    }
    
}

//Refresh current frame
void Simulator::Draw()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    //Draw dots
    for (Dot* dot : _dots) { dot->Draw(); }

    //Draw sticks
    for (Stick* stick : _sticks) { stick->Draw(); }

    //Draw structures
    _cloth->Draw();

    //Render to screen
    SDL_RenderPresent(_renderer);
}

//Destructor
Simulator::~Simulator()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);

    //Deallocate dots in vector
    for(Dot* dot : _dots) {
        SDL_DestroyTexture(dot->getTexture());
        delete dot;
        }

    //Deallocate sticks
    for(Stick* stick : _sticks) {delete stick; }

    delete _cloth;

    delete _engine;

    for (Point* point : _points) { delete point; }
}


