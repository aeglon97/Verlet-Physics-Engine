#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"
#include "controller.h"

class Game
{
public:
    void Run(Renderer& renderer, Controller& controller);

private:
};

#endif