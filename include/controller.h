#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"
class Renderer;

class Controller
{
public:
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL,
    };
    Controller();

    SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    //getters/setters
    SDL_Surface* getKeyPressSurface(KeyPressSurfaces keyPress) { return keyPressSurfaces[keyPress]; }
    void HandleEvents(SDL_Event e, Renderer &renderer);

    //setters/getters
    void toggleQuit(bool flag);
    bool hasQuit(){ return _quit; }
    
private:
    bool _quit{false};
};


#endif