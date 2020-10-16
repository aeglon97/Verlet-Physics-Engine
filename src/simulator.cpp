#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "simulator.h"

void Simulator::Run(Renderer& renderer, Controller& controller)
{
    if (!renderer.Init())
    {
        std::cerr << "SDL failed to initialize." << std::endl;
    }
    else
    {
        
        SDL_Event e;

        while (!controller.hasQuit())
        {
            //Handle events
            controller.HandleEvents(e);

            //Handle media
            if(!renderer.LoadMedia())
            {
                std::cerr << "Failed to load media." << std::endl;
            }
            else
            {
                SDL_BlitSurface(renderer.getHelloWorld(), NULL, renderer.getScreenSurface(), NULL);
                SDL_UpdateWindowSurface(renderer.getWindow());
            }

            //Insert activity
        }   
    }
    renderer.Close();
}
    
