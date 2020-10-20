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

        //Enable key press mode
        // SDL_Surface* keyPressDefaultSurface = controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DEFAULT];
        // renderer.SetCurrentSurface(keyPressDefaultSurface);

        while (!controller.hasQuit())
        {
            //Handle events
            controller.HandleEvents(e, renderer);

            //Handle media
            if(!renderer.LoadMedia(controller))
            {
                std::cerr << "Failed to load media." << std::endl;
            }
            else
            {
                //Key press code
                // SDL_BlitSurface(renderer.getCurrentSurface(), NULL, renderer.getScreenSurface(), NULL);
                // SDL_UpdateWindowSurface(renderer.getWindow());

                //??
                // SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
                // SDL_RenderClear(renderer.getRenderer());
                SDL_RenderCopy(renderer.getRenderer(), renderer.getTexture(), NULL, NULL); 

                // top left viewport
                renderer.RenderViewport(0, 0, renderer.getScreenWidth() / 2, renderer.getScreenHeight() / 2);
                //top right viewport
                renderer.RenderViewport(renderer.getScreenWidth() / 2, 0, renderer.getScreenWidth() / 2, renderer.getScreenHeight() / 2);
                //bottom viewport
                renderer.RenderViewport(0, renderer.getScreenHeight() / 2, renderer.getScreenWidth(), renderer.getScreenHeight() / 2);    

                //Update screen
                SDL_RenderPresent(renderer.getRenderer());  
            }

            //Load geometric shapes
            // renderer.RenderGeometry();
            
            //Insert activity
        }   
    }
    renderer.Close();
}
    
