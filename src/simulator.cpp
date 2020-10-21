#include "simulator.h"
#include <random>

Simulator::Simulator(const int screenWidth, const int screenHeight) 
    : _screenWidth(screenWidth), 
     _screenHeight(screenHeight)
{
    //Initialize window
    if (!SetupWindow())
    {
        std::cerr << "Failed to set up window. Error: " << SDL_GetError() << std::endl;
        return;
    }

    //Initialize sprites
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disWidth(1, _screenWidth);
    std::uniform_int_distribution<> disHeight(1, _screenHeight);
    _dot.SetPosition(_window, gen, disWidth, disHeight);
}

//Initialize window
bool Simulator::SetupWindow()
{
    bool success = true;
    
    //Create window
    // _window = SDL_CreateWindow("Verlet Physics Engine",
    //                             SDL_WINDOWPOS_CENTERED,
    //                             SDL_WINDOWPOS_CENTERED,
    //                             _screenWidth, _screenHeight, 0);

    if(_window == nullptr)
    {
        std::cerr << "Failed to create window. Error: " << SDL_GetError() << std::endl;
        return !success;
    }
    //UNCOMMENT BELOW IF NOT DEALING WITH TEXTURE CODE
    _windowSurface = SDL_GetWindowSurface(_window);
    if (_windowSurface == nullptr)
    {
        std::cerr << "Failed to retrieve window surface. Error: " << SDL_GetError() << std::endl;
        return !success;
    }
    return success;
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

    //Render texture to screen
    // SDL_FillRect(_windowSurface, nullptr, SDL_MapRGB(_windowSurface->format, 255, 255, 255));
    _dot.Draw(_renderer);
    // SDL_UpdateWindowSurface(_window);

    //Update screen
    SDL_RenderPresent(_renderer);
}

//Destructor
Simulator::~Simulator()
{
    SDL_FreeSurface(_windowSurface);
    SDL_DestroyWindow(_window);
}

//Load from file
SDL_Surface* Simulator::LoadSurface(const char* path)
{
    SDL_Surface *imageSurface = SDL_LoadBMP(path);
    return imageSurface == nullptr ? 0 : imageSurface;
}