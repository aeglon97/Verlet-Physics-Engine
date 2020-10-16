#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"

class Controller;

Renderer::Renderer(const int screenWidth, const int screenHeight)
    : _screenWidth(screenWidth), 
      _screenHeight(screenHeight){}

SDL_Surface* Renderer::LoadSurface(const char* path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if(!loadedSurface)
    {
        std::cout << "Unable to load image. Error: " << SDL_GetError() << std::endl;
    }
    return loadedSurface;
}

bool Renderer::LoadMedia(Controller &controller)
{
    //Loading success flag
    bool success = true;

    //Load default surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DEFAULT] = LoadSurface("../img/press.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout << "Failed to load default image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_UP] = LoadSurface("../img/up.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DOWN] = LoadSurface("../img/down.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_LEFT] = LoadSurface("../img/left.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_RIGHT] = LoadSurface("../img/right.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
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

void Renderer::SetCurrentSurface(SDL_Surface* surface)
{
    _currentSurface = surface;
}

void Renderer::Close()
{   
    //Deallocate surface
    SDL_FreeSurface(_currentSurface);
    _currentSurface = NULL;
    SDL_DestroyWindow(_window);
    SDL_Quit();
}