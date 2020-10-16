#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "controller.h"

Controller::Controller()
{
    this->keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
}

// SDL_Surface* Controller::getKeyPressSurface(KeyPressSurfaces keyPress)
// {

// }

void Controller::HandleEvents(SDL_Event e, Renderer &renderer)
{
    std::cout << "polling event object" << std::endl;
    
    while(SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            _quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //Select surface based on input
                case SDLK_UP:
                renderer.SetCurrentSurface(keyPressSurfaces[KEY_PRESS_SURFACE_UP]);
                break;

                case SDLK_DOWN:
                renderer.SetCurrentSurface(keyPressSurfaces[KEY_PRESS_SURFACE_DOWN]);
                break;

                case SDLK_LEFT:
                renderer.SetCurrentSurface(keyPressSurfaces[KEY_PRESS_SURFACE_LEFT]);
                break;

                case SDLK_RIGHT:
                renderer.SetCurrentSurface(keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]);
                break;

                default:
                renderer.SetCurrentSurface(keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]);
                break;
            }
        }
    }
}

void Controller::toggleQuit(bool flag)
{
    _quit = flag;
}