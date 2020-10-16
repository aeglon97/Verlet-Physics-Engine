#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

class Controller
{
public:
    void HandleEvents(SDL_Event e);

    //setters/getters
    void toggleQuit(bool flag);
    bool hasQuit(){ return _quit; }
    
private:
    bool _quit{false};
};


#endif