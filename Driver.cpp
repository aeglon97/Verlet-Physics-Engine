#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 1080;

//Main window to render to
SDL_Window* gWindow = NULL;

//Window surface (sceen)
SDL_Surface* gScreenSurface = NULL;

//Image to load and render on screen
SDL_Surface* gLion = NULL;

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


bool LoadMedia(const char* imgPath)
{
    bool success = true;

    //Load bmp image
    gLion = SDL_LoadBMP(imgPath);
    if (gLion == NULL)
    {
        std::cout << "Failed to load image " << "./lion.bmp" << '\nError: ' << SDL_GetError() << std::endl;
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
        if(e.type == SDL_QUIT)
        {
            quit = true;
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

        //Game lifetime
        while(!quit)
        {
            HandleEvents(e);

            //Load media
            if (!LoadMedia("./img/lion.bmp"))
            {
                std::cout << "Failed to load media. Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                //Apply image
                SDL_BlitSurface(gLion, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }    
        }
    }
    Close();
    return 0;
}

