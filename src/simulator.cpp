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

                // SDL_RenderPresent(renderer.getRenderer()); 
                //KEY PRESS CODE
                // SDL_BlitSurface(renderer.getCurrentSurface(), NULL, renderer.getScreenSurface(), NULL);
                // SDL_UpdateWindowSurface(renderer.getWindow());

                //VIEWPORT CODE
                // SDL_RenderClear(renderer.getRenderer());
                // SDL_RenderCopy(renderer.getRenderer(), renderer.getTexture(), NULL, NULL); 

                // top left viewport
                // renderer.RenderViewport(0, 0, renderer.getScreenWidth() / 2, renderer.getScreenHeight() / 2);
                // //top right viewport
                // renderer.RenderViewport(renderer.getScreenWidth() / 2, 0, renderer.getScreenWidth() / 2, renderer.getScreenHeight() / 2);
                // //bottom viewport
                // renderer.RenderViewport(0, renderer.getScreenHeight() / 2, renderer.getScreenWidth(), renderer.getScreenHeight() / 2);    

                //DRAW RECTANGLE
                // SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
                // SDL_RenderClear(renderer.getRenderer());

                // SDL_Rect rect = {renderer.getScreenWidth()/ 4, renderer.getScreenHeight() / 4,
                //                 40, 40};
                // // SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 255, 0, 255);
                // SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
                // SDL_RenderDrawRect( renderer.getRenderer(), &rect );
                
                //Update screen
                 

                //Draw
                

                // renderer.RenderGeometry();
            }

            //Load geometric shapes
            renderer.Draw();
            
            //Insert activity
        }   
    }
    renderer.Close();
}
    
