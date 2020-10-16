#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

class Renderer
{
public:
    Renderer(const int screenWidth, const int screenHeight);
    ~Renderer();
    bool Init();

    //getters/setters
    const int getScreenWidth() { return _screenWidth; }
    const int getScreenHeight() { return _screenHeight; }
    SDL_Window* getWindow() { return _window; }
    SDL_Surface* getScreenSurface() { return _screenSurface; }

private:
    SDL_Window* _window{NULL};
    SDL_Surface* _screenSurface{NULL};
    const int _screenWidth{0};
    const int _screenHeight{0};
};

#endif