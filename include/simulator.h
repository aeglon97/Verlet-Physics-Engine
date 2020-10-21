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
    void SetupWindow();
    ~Simulator();

    void Loop();
    void Update(double deltaTime);
    void Draw();

    //Pass to initializer list
    SDL_Window* InitializeWindow();
    SDL_Renderer* InitializeRenderer();

private:
    //Window attributes
    const int _screenWidth;
    const int _screenHeight;
    SDL_Window *_window;
    SDL_Surface *_windowSurface;
    SDL_Event _windowEvent;
    SDL_Renderer* _renderer;

    Dot _dot;
};



#endif