#ifndef DOT_H
#define DOT_H

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>

class Dot
{
public:
    Dot();
    ~Dot() = default;

    bool LoadImage(const char* path);
    void SetPosition(SDL_Window* window, std::mt19937 gen, 
                    std::uniform_int_distribution<> disWidth, 
                    std::uniform_int_distribution<> disHeight);
    void Update(double deltaTime);
    void Draw(SDL_Surface* windowSurface);
    void HandleEvents(SDL_Event const &e);

private:
    SDL_Surface *_image;
    SDL_Rect _imagePos;
    double _imageX;
    double _imageY;
};



#endif