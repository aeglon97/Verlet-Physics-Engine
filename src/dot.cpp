#include "dot.h"

Dot::Dot()
{
    //Load image
    if (!LoadImage())
    {
        std::cerr << "Failed to render dot.bmp in constructor. Error: " << SDL_GetError() << std::endl;
        return;
    }
}

//Manually set position of Dot
void Dot::SetPosition(SDL_Window* window, std::mt19937 gen, std::uniform_int_distribution<> disWidth, std::uniform_int_distribution<> disHeight)
{
    //Coordinates : randomly generate on screen
    _imagePos.x = 0;
    _imagePos.y = 0;
    _imagePos.w = 100;
    _imagePos.h = 100;

    _imageX = disWidth(gen);
    _imageY = disHeight(gen);
}


//Initialize Dot position and image
bool Dot::LoadImage()
{
    bool success = true;
    _image = SDL_LoadBMP("../img/dot.bmp");
    if (_image == nullptr)
    {
        std::cerr << "Failed to render dot.bmp. Error: " << SDL_GetError() << std::endl;
        return !success;
    }
    return success;
}

void Dot::Update(double deltaTime)
{
    _imageX = _imageX + (5 * deltaTime);
    _imagePos.x = _imageX;
}

void Dot::Draw(SDL_Surface* windowSurface)
{   
    //Connect image to image position
    SDL_BlitSurface(_image, nullptr, windowSurface, &_imagePos);
}