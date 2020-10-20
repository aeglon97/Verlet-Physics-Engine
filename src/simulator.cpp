#include "simulator.h"

Simulator::Simulator(const int screenWidth, const int screenHeight) : _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    //Initialize window
    _window = SDL_CreateWindow("Verlet Physics Engine",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _screenWidth, _screenHeight, 0);

    if(_window == NULL)
    {
        std::cerr << "Failed to create window. Error: " << SDL_GetError() << std::endl;
        return;
    }

    _windowSurface = SDL_GetWindowSurface(_window);

    if (_windowSurface == NULL)
    {
        std::cerr << "Failed to retrieve window surface. Error: " << SDL_GetError() << std::endl;
        return;
    }

    //ASSIGN SPRITE
    _image = LoadSurface("../img/dot.bmp");
    //Sprite coordinates
    _imagePos.x = 0;
    _imagePos.y = 0;
    _imagePos.w = 22;
    _imagePos.h = 43;

    _imageX = 0.0;
    _imageY = 0.0;

}

//Infinite while loop checking game state
void Simulator::Loop()
{
    bool running = true;
    while(running)
    {

        //Handle events
        while(SDL_PollEvent(&_windowEvent) != 0)
        {
            //Handle user input
            switch(_windowEvent.type)
            {
                case SDL_QUIT:
                running = false;
                break;
            }
        }
        
        //Animate sprites
        this->Update(1.0/60.0);
        this->Draw();
    }
}

//Account for frame rate
void Simulator::Update(double deltaTime)
{   
    _imageX = _imageX + (5 * deltaTime);
    _imagePos.x = _imageX;
}

//Refresh current frame
void Simulator::Draw()
{
    SDL_UpdateWindowSurface(_window);
    SDL_FillRect(_windowSurface, NULL, SDL_MapRGB(_windowSurface->format, 0, 0, 0));
    SDL_BlitSurface(_image, NULL, _windowSurface, &_imagePos);
}

//Destructor
Simulator::~Simulator()
{
    SDL_FreeSurface(_windowSurface);
    SDL_DestroyWindow(_window);
}

//Load from file
SDL_Surface* Simulator::LoadSurface(const char* path)
{
    SDL_Surface *imageSurface = SDL_LoadBMP(path);
    return imageSurface == NULL ? 0 : imageSurface;
}