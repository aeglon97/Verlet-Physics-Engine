#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "dot.h"

Dot::Dot()
{
    _posX = 0;
    _posY = 0;

    _velX = 0;
    _velY = 0;
}

void Dot::HandleEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: _velY -= DOT_VEL; break;
            case SDLK_DOWN: _velY += DOT_VEL; break;
            case SDLK_LEFT: _velX -= DOT_VEL; break;
            case SDLK_RIGHT: _velX += DOT_VEL; break;
        }
    }
    //If key is released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: _velY -= DOT_VEL; break;
            case SDLK_DOWN: _velY += DOT_VEL; break;
            case SDLK_LEFT: _velX -= DOT_VEL; break;
            case SDLK_RIGHT: _velX += DOT_VEL; break;
        }
    }
}

void Dot::move(Renderer &renderer)
{
    //Move dot left/right
    _posX += _velX;

    if((_posX < 0) || (_posX + DOT_WIDTH > renderer.getScreenWidth()))
    {
        //Move back
        _posX -= _velX;
    }

    //Move dot up/down
    _posY += _velY;

    if((_posY < 0) || (_posX + DOT_HEIGHT > renderer.getScreenHeight()))
    {
        //Move back
        _posY -= _velY;
    }
}

void Dot::render(Renderer &renderer)
{
    //Show dot
    
}