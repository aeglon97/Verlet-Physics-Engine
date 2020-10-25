#include "dot.h"

Dot::Dot(double radius) : _radius(radius)
{
    _diameter = _radius * 2;

    _imagePos.w = _diameter;
    _imagePos.h = _diameter;

    //Initialize motion variables

    //Slow down velocity with each collision
    _bounce = .8;
    _gravity = 0.0025;
    _friction = 1;
}

//Manually set position of Dot
void Dot::SetPosition(const int x, const int y)
{
    _imageX = x + _radius;
    _imageY = y + _radius;

    _oldX = _imageX - 2;
    _oldY = _imageY - 2;;

    _imagePos.x = _imageX;
    _imagePos.y = _imageY +_gravity;
}

//Initialize dot texture
void Dot::AssignTexture(const char* path)
{
    //Initialize image loaders
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initiatedFlags = IMG_Init(flags);

    if((initiatedFlags & flags) != flags)
    {
        std::cerr << "Failed to properly initialize image loaders. Error: " << SDL_GetError() << std::endl;
        return;
    }

    //Load image at path
    SDL_Surface* imageSurface = IMG_Load(path);
    if (imageSurface == nullptr)
    {
        std::cerr << "Failed to load dot.bmp surface. Error: " << SDL_GetError() << std::endl;
        return;
    }

    //Create texture from surface pixels
    _texture = SDL_CreateTextureFromSurface(_renderer, imageSurface);
    if (_texture == nullptr)
    {
        std::cerr << "Failed to load dot.bmp texture. Error: " << SDL_GetError() << std::endl;
        return;
    }
}

//When dot is at edge of window
void Dot::ApplyConstraints()
{
    double windowWidth = SDL_GetWindowSurface(_window)->w;
    double windowHeight = SDL_GetWindowSurface(_window)->h;

    //X on left side 
    if(_imageX < 0) 
    {
        _imageX = 0;
        //If going left, go right
        if (_velX < 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //X on right side
    if(_imageX + _diameter > windowWidth)
    {
        _imageX = windowWidth - _diameter;
        
        //If going right, go left
        if (_velX > 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //Y at top
    if(_imageY < 0)
    {
        _imageY = 0;

        //If going up, go down
        if(_velY < 0)
        {
            _velY = _velY * -1 * _bounce;
        }
    }

    //Y at bottom
     if(_imageY + _diameter > windowHeight)
    {
        _imageY = windowHeight - _diameter;
        //If going down, go up
        if(_velY > 0)
        {
            _velY = _velY * -1 * _bounce;
        }
    }
}

//Handle motion logic and states
void Dot::Update(double deltaTime)
{
    if(!_pinned)
    {
        //Setup velocity + timesteps
        _velX = (_imageX - _oldX) * _friction;
        _velY = (_imageY - _oldY) * _friction;  

        ApplyConstraints();

        _oldX = _imageX;
        _oldY = _imageY;

        //Move dot
        _imageX = _imageX + _velX;  
        _imageY = _imageY + _velY;
        _imageY += _gravity;
        
        //Update window coordinates
        _imagePos.x = _imageX;
        _imagePos.y = _imageY;
    }
}

//Render texture to screen
void Dot::Draw()
{  
    if(!_hidden)
    {
        SDL_RenderCopy(_renderer, _texture, NULL, &_imagePos);
    }
}

void Dot::HandleEvents(SDL_Event const &e)
{
    switch(e.type)
    {
        //Get dragged when held down by left mouse click
        if(e.key.keysym.sym == SDL_KEYDOWN);
        {
            std::cout << "left mouse clicked";
            this->Pin(false);
        }
    }
}
