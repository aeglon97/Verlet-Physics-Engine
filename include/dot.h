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
    
    bool LoadTexture(const char* path);
    void SetPosition(SDL_Window* window, const int xMax, const int yMax);
    void Update(double deltaTime);
    void Draw();
    void HandleEvents(SDL_Event const &e);

    //getters/setters
    // SDL_Renderer* getRenderer() { return _renderer; }
    SDL_Surface* getImage() { return _image; }
    SDL_Texture* getTexture() { return _texture; }
    double getX() { return _imageX; }
    double getY() { return _imageY; }
    void setRenderer(SDL_Window* window);

    //Motion handlers
    void ApplyConstraints();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    //Dot properties
    SDL_Surface *_image;
    SDL_Rect _imagePos;
    double _imageX;
    double _imageY;
    double _oldX;
    double _oldY;

    double _radius;
    
    //Motion variables
    double _velX;
    double _velY;
    double _bounce;
    double _gravity;

    //Current displayed texture
    SDL_Texture *_texture;
};



#endif