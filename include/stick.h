#ifndef STICK_H
#define STICK_H

#include "dot.h"

class Stick
{
public:
    Stick(Dot* a, Dot* b);
    void Update();
    void Draw();


    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
    void setWindow(SDL_Window* window) { _window = window; }
    //Pass to initializer list
    double InitializeLength();
    void Hide(bool hide) { _hidden = hide; }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    //Dot properties
    Dot* _dotA;
    Dot* _dotB;

    //Motion variables
    double _length;
    double _deltaX;
    double _deltaY;

    bool _hidden{false};

};

#endif