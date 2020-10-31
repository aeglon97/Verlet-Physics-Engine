#include "point.h"

Point::Point(double velX, double velY) : 
    _velX(velX), _velY(velY)
{

}

Point::~Point()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Point::setPosition(double x, double y)
{
    _x = x;
    _y = y;

    _oldX = _x - _velX;
    _oldY = _y - _velY;

    // _imagePos.x = _x;
    // _imagePos.y = _y +_gravity;
}

void Point::Update(double deltaTime)
{
    if(!_pinned)
    {
        //Setup velocity + timesteps
        _velX = (_x - _oldX) * _friction;
        _velY = (_y - _oldY) * _friction;  

        ApplyConstraints();

        _oldX = _x;
        _oldY = _y;

        //Move dot
        _x = _x + _velX;  
        _y = _y + _velY;
        _y += _gravity;
        
        //Update window coordinates
        // _imagePos.x = _x;
        // _imagePos.y = _y;
    }
}

void Point::ApplyConstraints()
{
    double windowWidth = SDL_GetWindowSurface(_window)->w;
    double windowHeight = SDL_GetWindowSurface(_window)->h;

    //X on left side 
    if(_x < 0) 
    {
        _x = 0;
        //If going left, go right
        if (_velX < 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //X on right side
    if(_x > windowWidth)
    {
        _x = windowWidth;
        
        //If going right, go left
        if (_velX > 0)
        {
            _velX = _velX * -1 * _bounce;
        }
    }

    //Y at top
    if(_y < 0)
    {
        _y = 0;

        //If going up, go down
        if(_velY < 0)
        {
            _velY = _velY * -1 * _bounce;
        }
    }

    //Y at bottom
     if(_y > windowHeight)
    {
        _y = windowHeight;
        //If going down, go up
        if(_velY > 0)
        {
            _velY = _velY * -1 * _bounce;
        }
    }
}