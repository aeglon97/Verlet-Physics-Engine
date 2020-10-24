#ifndef STICK_H
#define STICK_H

#include "dot.h"

class Stick
{
public:
    Stick(Dot* a, Dot* b, SDL_Window* window, SDL_Renderer* renderer);
    void Update();
    void Draw();

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