#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"

Renderer::Renderer(const int screenWidth, const int screenHeight)
    : _screenWidth(screenWidth), 
      _screenHeight(screenHeight){}

bool Renderer::LoadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    _helloWorld = SDL_LoadBMP( "../img/hello_world.bmp");
    if( _helloWorld == NULL )
    {
        std::cerr << "Failed to load default image." << std::endl;
        success = false;
    }

    return success;
}

bool Renderer::Init()
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;   
    }
    else
    {
        //Create window
        _window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN );
        // SDL_SetWindowResizable(gWindow, SDL_TRUE);
        if (_window == NULL)
        {
            std::cerr << "Failed to create window. Error: " << SDL_GetError() << std::endl;
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

void Renderer::Close()
{   
    //Deallocate surface
    SDL_FreeSurface(_helloWorld);
    _helloWorld = NULL;
    SDL_DestroyWindow(_window);
    SDL_Quit();
}