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
    Dot(SDL_Window* window, SDL_Renderer* renderer);
    ~Dot() = default;

    bool LoadImage(const char* path);
    bool LoadTexture(const char* path, SDL_Renderer* renderer);
    void SetPosition(SDL_Window* window, std::mt19937 gen, 
                    std::uniform_int_distribution<> disWidth, 
                    std::uniform_int_distribution<> disHeight);
    void Update(double deltaTime);
    void Draw(SDL_Renderer* renderer);
    void HandleEvents(SDL_Event const &e);

    //getters/setters
    // SDL_Renderer* getRenderer() { return _renderer; }
    SDL_Surface* getImage() { return _image; }
    SDL_Texture* getTexture() { return _texture; }

    void setRenderer(SDL_Window* window);

private:
    SDL_Surface *_image;
    SDL_Rect _imagePos;
    double _imageX;
    double _imageY;
    SDL_Window* _window;

    //Current displayed texture
    SDL_Texture *_texture;
};



#endif