#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"

Renderer::Renderer(const int screenWidth, const int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight)
    {
        Init();
    }

bool Renderer::Init()
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;   
    }
    else
    {
        //Create window
        _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN );
        // SDL_SetWindowResizable(gWindow, SDL_TRUE);
        if (_window == NULL)
        {
            std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Get window surface
            _screenSurface = SDL_GetWindowSurface(_window);
        }
    }
    return success;
}

Renderer::~Renderer()
{   
    SDL_DestroyWindow(_window);
    SDL_Quit();
}