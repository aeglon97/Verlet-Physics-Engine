#ifndef SIMULATOR_H
#define SIMULATOR_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "dot.h"

class Dot;

class Simulator
{
public:
    Simulator(const int screenWidth, const int screenHeight);
    bool SetupWindow();
    ~Simulator();

    void Loop();
    void Update(double deltaTime);
    void Draw();
    SDL_Surface *LoadSurface(const char* path);

private:
    //Window attributes
    const int _screenWidth;
    const int _screenHeight;
    SDL_Window *_window = SDL_CreateWindow("Verlet Physics Engine",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _screenWidth, _screenHeight, 0);
    SDL_Surface *_windowSurface;
    SDL_Event _windowEvent;
    SDL_Renderer* _renderer = SDL_CreateRenderer(_window,-1, SDL_RENDERER_ACCELERATED);

    Dot _dot = Dot(_window, _renderer);
};



#endif