#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"
class Renderer;

class Dot
{
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    static const int DOT_VEL = 10;

    Dot();
    void HandleEvent(SDL_Event& e);

    void move(Renderer &renderer);
    void render(Renderer &renderer);
private:
    int _posX, _posY;
    int _velX, _velY;

};

#endif