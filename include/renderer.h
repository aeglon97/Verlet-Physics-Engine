#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "controller.h"

class Controller;
class Texture;

class Renderer
{
public:
    Renderer(const int screenWidth, const int screenHeight);
    
    bool Init();
    void Draw();
    bool LoadMedia(Controller &controller);
    void Close();
    SDL_Surface* LoadSurface(const char* path);

    //Texture handling
    SDL_Texture* LoadTexture(const char* path);


    //getters/setters
    const int getScreenWidth() { return _screenWidth; }
    const int getScreenHeight() { return _screenHeight; }
    SDL_Window* getWindow() { return _window; }
    SDL_Surface* getScreenSurface() { return _screenSurface; }
    SDL_Surface* getCurrentSurface() { return _currentSurface; }
    SDL_Surface* getStretchedSurface() { return _stretchedSurface; }

    void SetCurrentSurface(SDL_Surface* surface);
    SDL_Rect CreateStretchedRect();
    void DisplayFullSize(SDL_Rect rect);

    void setRenderer(SDL_Window*, int i) {
        _renderer = SDL_CreateRenderer(_window, i, SDL_RENDERER_ACCELERATED);
    }

    void RenderGeometry(); 

    SDL_Renderer* getRenderer() { return _renderer; }

    SDL_Texture* getTexture() { return _texture; }

    void RenderViewport(int x, int y, int width, int height);

private:
    SDL_Window* _window{NULL};
    SDL_Surface* _screenSurface{NULL};
    SDL_Surface* _currentSurface{NULL};
    SDL_Surface* _stretchedSurface{NULL};
    SDL_Event _windowEvent;

    //Built-in renderer
    SDL_Renderer* _renderer{NULL};
    SDL_Texture* _texture{NULL};
    
    //Moving dot
    SDL_Surface *_image;
    SDL_Rect _imagePos;

    const int _screenWidth{0};
    const int _screenHeight{0};
};

#endif