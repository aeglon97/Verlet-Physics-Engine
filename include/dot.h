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
    void SetPosition(const int xMax, const int yMax);
    void Update(double deltaTime);
    void Draw();
    void HandleEvents(SDL_Event const &e);

    void Pin(bool pin) { _pinned = pin; }
    bool Pinned() { return _pinned; }

    //getters/setters

    // SDL_Renderer* getRenderer() { return _renderer; }
    SDL_Surface* getImage() { return _image; }
    SDL_Texture* getTexture() { return _texture; }
    double getX() { return _imageX; }
    double getY() { return _imageY; }
    double getRadius() { return _radius; }
    void setRenderer(SDL_Window* window);

    //Coordinate offsetting
    double getCenterX() { return _imageX + _radius; }
    double getCenterY() { return _imageY + _radius; }

    //Motion handlers
    void ApplyConstraints();
    void setX(double x) { _imageX = x; }
    void setY(double y) { _imageY = y; }


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
    double _diameter;
    
    //Motion variables
    double _velX;
    double _velY;
    double _bounce{1};
    double _gravity{0.};
    double _friction{1.0};
    bool _pinned{false};
    //Current displayed texture
    SDL_Texture *_texture;
};

#endif