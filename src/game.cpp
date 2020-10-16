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
        bool quit = false;
        SDL_Event e;

        while (!quit)
        {
            //Handle events
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                    
                }
            }

            //Handle media
            if(!renderer.LoadMedia())
            {
                std::cout << "Failed to load media." << std::endl;
            }
            else
            {
                SDL_BlitSurface(renderer.getHelloWorld(), NULL, renderer.getScreenSurface(), NULL);
                SDL_UpdateWindowSurface(renderer.getWindow());
            }

            //Update
            
        }   
    }
    renderer.Close();
}
    
