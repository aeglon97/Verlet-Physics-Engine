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

    _radius = 20;

    //Initialize motion variables
    //Slow down velocity with each collision
    _bounce = 0.9;
    _gravity = 0.0025;
}

//Manually set position of Dot
void Dot::SetPosition(SDL_Window* window, const int xMax, const int yMax)
{
    //Randomly generate starting coordinates
    _imageX = rand() % xMax;
    _imageY = rand() % yMax;

    _oldX = _imageX - 0.25;
    _oldY = _imageY - 0.25;

    _imagePos.x = _imageX;
    _imagePos.y = _imageY;

    std::cout << "vX: " << _imageX - _oldX << std::endl;
    std::cout << "vY: " << _imageY - _oldY << std::endl;
    std::cout << "-----------------" << std::endl;
    
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

//When dot is at edge of window
void Dot::ApplyConstraints()
{
    double windowWidth = SDL_GetWindowSurface(_window)->w;
    double windowHeight = SDL_GetWindowSurface(_window)->h;

    //X on left side 
    if(_imageX + _radius <= 0) 
    {
        // _imageX = 0;
        //If going left, go right
        if (_velX < 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //X on right side
    if(_imageX + _radius > windowWidth)
    {
        _imageX = windowWidth - _radius;
        
        //If going right, go left
        if (_velX > 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //Y at top
    if(_imageY + _radius < 0)
    {
        // _imageY = 0;
        //If going up, go down
        if(_velY < 0)
        {
            _velY = _velY *- 1 * _bounce;
        }
    }

    //Y at bottom
     if(_imageY + _radius > windowHeight)
    {
        _imageY = windowHeight - _radius;
        //If going down, go up
        if(_velY > 0)
        {
            _velY = (_velY *- 1) * _bounce;
        }
    }
}

//Handle motion logic and states
void Dot::Update(double deltaTime)
{
    
    //Velocity + timesteps
    _velX = (_imageX - _oldX);
    _velY = (_imageY - _oldY);  

    ApplyConstraints();

    _oldX = _imageX;
    _oldY = _imageY;

    _imageX = _imageX + _velX;
    _imageY = _imageY + _velY;
    _imageY += _gravity;
    
    //Update window coordinates
    _imagePos.x = _imageX;
    _imagePos.y = _imageY;
    
}


//Render directly to window surface
void Dot::Draw()
{   
    //Render texture to screen
    SDL_Rect RenderQuad = {_imagePos.x, _imagePos.y, _radius * 2, _radius * 2};
    SDL_RenderCopy(_renderer, _texture, NULL, &RenderQuad);
    // std::cout << _imageY << std::endl;
}

void Dot::HandleEvents(SDL_Event const &e)
{
    switch(e.type)
    {
        //Get dragged when held down by left mouse click
    }
}
