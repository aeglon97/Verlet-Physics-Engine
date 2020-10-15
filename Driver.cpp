#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
//Key press events constants
enum KeyPressSurface
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 1080;

//Main window to render to
SDL_Window* gWindow = NULL;

//Window surface (sceen)
SDL_Surface* gScreenSurface = NULL;

//Image to load and render on screen
SDL_Surface* gLion = NULL;

//Map key presses to images
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;


//Game state
bool quit;

bool Init()
{
    //Init flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;   
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        // SDL_SetWindowResizable(gWindow, SDL_TRUE);
        if (gWindow == NULL)
        {
            std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}


//Load individual image
SDL_Surface* loadSurface(const char* path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image. Error: " << SDL_GetError() << std::endl;
    }
    return loadedSurface;
}

//Load images based on surface state
bool LoadMedia()
{
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./img/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout << "Failed to load default image." << std::endl;
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./img/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout << "Failed to load up image." << std::endl;
        success = false;
    }


    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./img/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout << "Failed to load down image." << std::endl;
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./img/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout << "Failed to load left image." << std::endl;
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./img/right.bmp");
     if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout << "Failed to load right image." << std::endl;
        success = false;
    }

    return success;
}

void Close()
{
    //Deallocate surface from memory
    SDL_FreeSurface(gLion);
    gLion = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

}

//Handle events on queue
void HandleEvents(SDL_Event e)
{
    while(SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }

        //Change surface state according to keyboard input
        else if (e.type = SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                break;

                case SDLK_DOWN:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                break;

                case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                break;

                case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                break;

                default:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
        }
    }
}


int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!Init())
    {
        std::cout << "SDL failed to initialize." << std::endl;
    }
    else
    {
        //Main loop flag
        quit = false;

        //Event handler
        SDL_Event e;
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

        //Game lifetime
        while(!quit)
        {
            HandleEvents(e);

            //Load media
            if (!LoadMedia())
            {
                std::cout << "Failed to load media. Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                //Apply image
            }    
        }
    }
    Close();
    return 0;
}

