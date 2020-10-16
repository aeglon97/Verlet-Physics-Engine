#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "controller.h"

class Controller;

class Renderer
{
public:
    Renderer(const int screenWidth, const int screenHeight);
    // ~Renderer();
    bool Init();
    bool LoadMedia(Controller &controller);
    void Close();
    SDL_Surface* LoadSurface(const char* path);

    //getters/setters
    const int getScreenWidth() { return _screenWidth; }
    const int getScreenHeight() { return _screenHeight; }
    SDL_Window* getWindow() { return _window; }
    SDL_Surface* getScreenSurface() { return _screenSurface; }
    SDL_Surface* getCurrentSurface() { return _currentSurface; }

    void SetCurrentSurface(SDL_Surface* surface);

private:
    SDL_Window* _window{NULL};
    SDL_Surface* _screenSurface{NULL};
    SDL_Surface* _currentSurface{NULL};

    const int _screenWidth{0};
    const int _screenHeight{0};
};

#endif