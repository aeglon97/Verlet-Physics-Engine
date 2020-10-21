#include "dot.h"

Dot::Dot(SDL_Window* window, SDL_Renderer* renderer) : _window(window)
{
    //Assign renderer


    //Load image
    if (!LoadTexture("../img/dot.bmp", renderer))
    {
        std::cerr << "Failed to render dot.bmp in constructor. Error: " << SDL_GetError() << std::endl;
        return;
    }
}

//Manually set position of Dot
void Dot::SetPosition(SDL_Window* window, std::mt19937 gen, 
                        std::uniform_int_distribution<> disWidth,
                        std::uniform_int_distribution<> disHeight)
{
    //Randomly generate starting coordinates
    _imagePos.x = disHeight(gen);
    _imagePos.y = disHeight(gen);
    _imagePos.w = 100;
    _imagePos.h = 100;

    _imageX = _imagePos.x;
    _imageY = _imagePos.y;
}


//Initialize texture
bool Dot::LoadTexture(const char* path, SDL_Renderer* renderer)
{
    //The final texture
    bool success = true;

    //Initialize image loaders
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initiatedFlags = IMG_Init(flags);

    if((initiatedFlags & flags) != flags)
    {
        std::cerr << "Failed to properly initialize image loaders. Error: " << SDL_GetError() << std::endl;
        return !success;
    }

    //Load image at path
    SDL_Surface* imageSurface = IMG_Load(path);
    if (imageSurface == nullptr)
    {
        std::cerr << "Failed to load dot.bmp surface. Error: " << SDL_GetError() << std::endl;
        return !success;
    }

    //Create texture from surface pixels
    _texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (_texture == nullptr)
    {
        std::cerr << "Failed to load dot.bmp texture. Error: " << SDL_GetError() << std::endl;
        return !success;
    }
    return success;
}

//Initialize Dot position and image
bool Dot::LoadImage(const char* path)
{
    bool success = true;
    SDL_Surface *optimizedSurface = nullptr;

    //Initialize image loaders
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initiatedFlags = IMG_Init(flags);

    if((initiatedFlags & flags) != flags)
    {
        std::cerr << "Failed to properly initialize image loaders. Error: " << SDL_GetError() << std::endl;
        return !success;
    }

    //Begin loading image
    SDL_Surface *imageSurface = IMG_Load(path);
    
    if (imageSurface == nullptr)
    {
        std::cerr << "Failed to load dot.bmp. Error: " << SDL_GetError() << std::endl;
        return !success;
    }

    optimizedSurface = SDL_ConvertSurface(imageSurface, imageSurface->format, 0);

    if (optimizedSurface == nullptr)
    {
         std::cerr << "Failed to optimize dot.bmp. Error: " << SDL_GetError() << std::endl;
        return !success;
    }

    _image = optimizedSurface;
    SDL_FreeSurface(imageSurface);
    return success;
}

//Handle motion logic and states
void Dot::Update(double deltaTime)
{
    _imageX = _imageX + (5 * deltaTime);
    _imagePos.x = _imageX;

    _imageY = _imageY + (5 * deltaTime);
    _imagePos.y = _imageY;
}

//Render directly to window surface
void Dot::Draw(SDL_Renderer* renderer)
{   
    //Connect image to image position
    // SDL_BlitSurface(_image, nullptr, windowSurface, &_imagePos);

    //Render texture to screen
    SDL_RenderCopy(renderer, _texture, NULL, &_imagePos);
}

void Dot::HandleEvents(SDL_Event const &e)
{
    switch(e.type)
    {
        //Get dragged when held down by left mouse click
    }
}

//Connect renderer to window
// void Dot::setRenderer(SDL_Window* window)
// {
//     std::cout << "Setting renderer" << std::endl;
//     _renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
//     if(_renderer == nullptr)
//     {
//         std::cerr << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
//     }
// }
