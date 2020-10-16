#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "controller.h"


void Controller::HandleEvents(SDL_Event e)
{
    while(SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            _quit = true;
        }
    }
}

void Controller::toggleQuit(bool flag)
{
    _quit = flag;
}