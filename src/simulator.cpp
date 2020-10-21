#include "simulator.h"
#include <random>


//Initialize window and renderer in initializer list
Simulator::Simulator(const int screenWidth, const int screenHeight) 
    :   _screenWidth(screenWidth),
        _screenHeight(screenHeight),
        _window(InitializeWindow()),
        _renderer(InitializeRenderer()),
        _dot{_window, _renderer}
{
    //Initialize sprite positions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disWidth(1, _screenWidth);
    std::uniform_int_distribution<> disHeight(1, _screenHeight);
    _dot.SetPosition(_window, gen, disWidth, disHeight);
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
    _dot.Update(deltaTime);
}

//Refresh current frame
void Simulator::Draw()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    _dot.Draw();

    //Update screen
    SDL_RenderPresent(_renderer);
}

//Destructor
Simulator::~Simulator()
{
    SDL_DestroyWindow(_window);
}

//Helper function : generate random number distribution
void SetDotPosition()
{
    
}


