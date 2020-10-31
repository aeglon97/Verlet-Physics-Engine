#ifndef POINT_H
#define POINT_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "engine.h"

class Engine;

class Point : public Engine
{
public:
    Point(double velX, double velY);
    ~Point();

    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
    void setWindow(SDL_Window* window) { _window = window; }
    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }
    void setPosition(double x, double y);
    void ApplyConstraints();

    //Velocity


    void Pin(bool pin) { _pinned = pin; }
    bool Pinned() { return _pinned; }

    void Update(double deltaTime);

    //Getters/setters
    SDL_Renderer* getRenderer() { return _renderer; }
    SDL_Window* getWindow() { return _window; }
    double getX() { return _x; }
    double getY() { return _y; }

private:
    //Main attributes
    SDL_Renderer* _renderer;
    SDL_Window* _window;

    bool _pinned{0};

    //Velocity
    double _velX;
    double _velY;

    //Position variables
    double _x;
    double _y;
    double _oldX;
    double _oldY;
};

#endif