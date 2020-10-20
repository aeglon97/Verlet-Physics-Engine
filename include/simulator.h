#ifndef SIMULATOR_H
#define SIMULATOR_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Simulator
{
public:
    Simulator(const int screenWidth, const int screenHeight);
    ~Simulator();

    void Loop();
    void Update(double deltaTime);
    void Draw();
    SDL_Surface *LoadSurface(const char* path);

private:
    //Window attributes
    const int _screenWidth;
    const int _screenHeight;
    SDL_Window *_window;
    SDL_Surface *_windowSurface;
    SDL_Event _windowEvent;

    //Sprite attributes
    SDL_Surface *_image;
    SDL_Rect _imagePos;
    double _imageX;
    double _imageY;
};







#endif