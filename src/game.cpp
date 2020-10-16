#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "game.h"

void Game::Run(Renderer& renderer)
{
    if (!renderer.Init())
    {
        std::cout << "SDL failed to initialize." << std::endl;
    }
    else
    {
        if(!renderer.LoadMedia())
        {
            std::cout << "Failed to load media." << std::endl;
        }
        else
        {
            SDL_BlitSurface(renderer.getHelloWorld(), NULL, renderer.getScreenSurface(), NULL);
            SDL_UpdateWindowSurface(renderer.getWindow());
            SDL_Delay(2000);
        }
        
        // bool running = true;
        // while(running)
        // {
        //     // DL_FillRect(_screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ));
        //     SDL_UpdateWindowSurface(renderer.getWindow());
        //     SDL_Delay(2000);
        //     running = false;
        // }
    }
}