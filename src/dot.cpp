#include "dot.h"

Dot::Dot(SDL_Window* window, SDL_Renderer* renderer) : _window(window), _renderer(renderer)
{
    srand((unsigned int)time(NULL));
    //Load image
    if (!LoadTexture("../img/dot.png"))
    {
        std::cerr << "Failed to render dot.bmp in constructor. Error: " << SDL_GetError() << std::endl;
        return;
    }
}

//Manually set position of Dot
void Dot::SetPosition(SDL_Window* window, const int xMax, const int yMax)
{
    //Randomly generate starting coordinates
    _imageX = rand() % xMax;
    _imageY = rand() % yMax;

    _imagePos.x = _imageX;
    _imagePos.y = _imageY;
    _imagePos.w = 40;
    _imagePos.h = 40;
}

//Resize Dot width and height

//Initialize dot texture
bool Dot::LoadTexture(const char* path)
{
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
    _texture = SDL_CreateTextureFromSurface(_renderer, imageSurface);
    if (_texture == nullptr)
    {
        std::cerr << "Failed to load dot.bmp texture. Error: " << SDL_GetError() << std::endl;
        return !success;
    }
    return success;
}

//Handle motion logic and states
void Dot::Update(double deltaTime)
{
    _imageX = _imageX + (5 * deltaTime);
    _imagePos.x = _imageX;

    _imageY = _imageY + (5 * deltaTime);
    _imagePos.y = _imageY;
    
    // std::cout << "New x: " << _imageX << " New y: " << _imageY << std::endl;
}


//Render directly to window surface
void Dot::Draw()
{   
    //Render texture to screen
    SDL_Rect RenderQuad = {_imagePos.x, _imagePos.y, _imagePos.w, _imagePos.h};
    SDL_RenderCopy(_renderer, _texture, NULL, &RenderQuad);
}

void Dot::HandleEvents(SDL_Event const &e)
{
    switch(e.type)
    {
        //Get dragged when held down by left mouse click
    }
}
