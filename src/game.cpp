#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "game.h"

Game::Game(const int screenWidth, const int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight)
    {
        Init();
    }

bool Game::Init()
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

void Game::Run()
{
    if (!Init())
    {
        std::cout << "SDL failed to initialize." << std::endl;
    }
    else
    {
        bool running = true;
        while(running)
        {
            // DL_FillRect(_screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ));
            SDL_UpdateWindowSurface(_window);
            SDL_Delay(2000);
            running = false;
        }
    }
    
}

Game::~Game()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}