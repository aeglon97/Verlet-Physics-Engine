#ifndef SIMULATOR_H
#define SIMULATOR_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "dot.h"
#include "stick.h"
#include "structure.h"

class Dot;
class Stick;

class Simulator
{
public:
    Simulator(const int screenWidth, const int screenHeight);
    void SetupWindow();
    ~Simulator();

    void Loop();
    void Update(double deltaTime);
    void UpdateSticks();
    void UpdateDots();
    void Draw();

    //Pass to initializer list
    void InitializeWindow();
    void InitializeRenderer();
    void InitializeDots(const int n);
    void InitializePoints(const int n);

    //Render entities
    void InitializeCloth(const int height, const int width);

private:
    //Window attributes
    const int _screenWidth;
    const int _screenHeight;
    SDL_Window *_window;
    SDL_Surface *_windowSurface;
    SDL_Event _windowEvent;
    SDL_Renderer* _renderer;

    //Render entities
    std::vector<Dot*> _dots;
    std::vector<Stick*> _sticks;
    std::vector<Structure*> _forms;
    Cloth* _cloth;

};



#endif