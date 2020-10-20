#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "renderer.h"

class Controller;

Renderer::Renderer(const int screenWidth, const int screenHeight)
    : _screenWidth(screenWidth), 
      _screenHeight(screenHeight){}

SDL_Texture* Renderer::LoadTexture(const char* path)
{   
    //Final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL)
    {
        std::cerr << "Unable to load image. Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if(newTexture == NULL)
        {
            std::cerr << "Unable to create texture from " << path << ". Error: " << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

SDL_Surface* Renderer::LoadSurface(const char* path)
{
    //Final optimized surface
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image. Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, _screenSurface->format, 0);
        if(optimizedSurface == NULL)
        {
            std::cerr << "Could not optimize image. Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool Renderer::LoadMedia(Controller &controller)
{
    //Loading success flag
    bool success = true;

    //Load PNG texture

    _texture = LoadTexture("../img/up.bmp");
    if(_texture == NULL)
    {
        std::cerr << "Failed to load texture image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load default surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DEFAULT] = LoadSurface("../img/press.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout << "Failed to load default image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    // Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_UP] = LoadSurface("../img/up.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DOWN] = LoadSurface("../img/down.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_LEFT] = LoadSurface("../img/left.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    //Load up surface
    controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_RIGHT] = LoadSurface("../img/right.bmp");
    if(controller.keyPressSurfaces[controller.KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout << "Failed to load up image. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

//Create viewport
void Renderer::RenderViewport(int x, int y, int width, int height)
{
    //Define viewport
    SDL_Rect viewport;
    viewport.x = x;
    viewport.y = y;
    viewport.w = width;
    viewport.h = height;
    SDL_RenderSetViewport( _renderer, &viewport );

    //Render texture to screen
    SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

//Generate static shapes
void Renderer::RenderGeometry()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render red-filled quad
    SDL_Rect fillRect = {_screenWidth/ 4, _screenHeight / 4, _screenWidth/ 2, _screenHeight / 2};
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF); 
    SDL_RenderFillRect(_renderer, &fillRect);

    //Render green outlined quadSDL_
    SDL_Rect outlineRect = { _screenWidth / 6, _screenHeight / 6, _screenWidth * 2 / 3, _screenHeight * 2 / 3 };
    SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );        
    SDL_RenderDrawRect( _renderer, &outlineRect );

    //Draw blue horizontal line
    SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0xFF, 0xFF );        
    SDL_RenderDrawLine( _renderer, 0, _screenHeight / 2, _screenWidth, _screenHeight / 2 );

    SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < _screenHeight; i += 4 )
    {
        SDL_RenderDrawPoint( _renderer, _screenWidth / 2, i );
    }
}

//Create window
bool Renderer::Init()
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;   
    }
    else
    {
        //Create window
        _window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN );
        // SDL_SetWindowResizable(gWindow, SDL_TRUE);
        if (_window == NULL)
        {
            std::cerr << "Failed to create window. Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Create renderer for window
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if(_renderer == NULL)
            {
                std::cerr << "Renderer could not be created. Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Get window surface
                _screenSurface = SDL_GetWindowSurface(_window);

                //Initialize renderer color
                SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cerr << "SDL_image could not initialize. Error: " << SDL_GetError() << std::endl;
                }    
            }
        }
    }
    return success;
}


void Renderer::SetCurrentSurface(SDL_Surface* surface)
{
    _currentSurface = surface;
}

//Free all resources in use
void Renderer::Close()
{   
    //Free loaded image
    SDL_DestroyTexture(_texture);
    _texture = NULL;

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_FreeSurface(_currentSurface);
    _currentSurface = NULL;
    _renderer = NULL;
    _window = NULL;

    //Quit SDL systems
    IMG_Quit();
    SDL_Quit();
}

//Create a rectangle filling up the whole screen
SDL_Rect Renderer::CreateStretchedRect()
{
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = _screenWidth;
    stretchRect.h = _screenHeight;
    return stretchRect;
}

//Convert current surface image to full size
void Renderer::DisplayFullSize(SDL_Rect rect)
{
    SDL_BlitScaled(_currentSurface, NULL, _screenSurface, &rect);   
    // SDL_UpdateWindowSurface(_window);
}