#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

class Game
{
public:
    Game(const int screenWidth, const int screenHeight);
    ~Game();
    bool Init();
    void Run();

private:
    SDL_Window* _window{NULL};
    SDL_Surface* _screenSurface{NULL};
    const int _screenWidth{0};
    const int _screenHeight{0};
};

#endif