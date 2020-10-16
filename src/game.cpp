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
        bool running = true;
        while(running)
        {
            // DL_FillRect(_screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ));
            SDL_UpdateWindowSurface(renderer.getWindow());
            SDL_Delay(2000);
            running = false;
        }
    }
}