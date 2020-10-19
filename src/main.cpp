#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include "simulator.h"

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 1080;

//Game state
bool quit;

int main(int argc, char* args[])
{
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    Controller controller;
    Simulator simulator;
    simulator.Run(renderer, controller);
    return 0;
}