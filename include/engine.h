#ifndef ENGINE_H
#define ENGINE_H

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>

class Engine
{
public:
    Engine() = default;
    ~Engine() = default;

    //Setters
    void setBounce(double bounce) { _bounce = bounce; }
    void setGravity(double gravity) { _gravity = gravity; }
    void setFriction(double friction) { _friction = friction; }

    //Getters
    double getBounce() { return _bounce; }
    double getGravity() { return _gravity; }
    double getFriction() { return _friction; }

protected:
    double _bounce{1};
    double _gravity{0};
    double _friction{1};
};

#endif