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
    Dot(double radius);
    ~Dot() = default;
    
    void AssignTexture(const char* path);
    void SetPosition(const int xMax, const int yMax);
    void Update(double deltaTime);
    void Draw();
    void HandleEvents(SDL_Event const &e);

    void Pin(bool pin) { _pinned = pin; }
    bool Pinned() { return _pinned; }

    void Hide(bool hide) { _hidden = hide; }

    //getters/setters

    SDL_Renderer* getRenderer() { return _renderer; }
    SDL_Surface* getImage() { return _image; }
    SDL_Texture* getTexture() { return _texture; }
    double getX() { return _imageX; }
    double getY() { return _imageY; }
    double getRadius() { return _radius; }

    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
    void setWindow(SDL_Window* window) { _window = window; }
    void setRadius(double radius) { _radius = radius; }

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
    SDL_Event* _eventHandler;
    //Dot properties
    SDL_Surface *_image;
    SDL_Rect _imagePos;
    double _imageX;
    double _imageY;
    double _oldX;
    double _oldY;

    double _radius;
    double _diameter;

    bool _hidden{0};
    
    //Motion variables
    double _velX;
    double _velY;
    double _bounce{1};
    double _gravity{0};
    double _friction{1};
    bool _pinned{false};
    //Current displayed texture
    SDL_Texture *_texture;
};

#endif