#include "stick.h"
#include <cmath>

Stick::Stick(Dot* dotA, Dot* dotB, SDL_Window* window, SDL_Renderer* renderer): _dotA(dotA),
_dotB(dotB), _length(InitializeLength()), _window(window), _renderer(renderer)
{
    
}

double Stick::InitializeLength()
{
    _deltaX = _dotA->getX() - _dotB->getY();
    _deltaY = _dotA->getY() - _dotB->getY();
    
    std::cout << _dotA->getX() << std::endl;
    return sqrt(pow(_deltaX, 2) + pow(_deltaY, 2));
}

void Stick::Update()
{
    //Calculate current length, compare to actual length
    double currentLength = InitializeLength();
    double difference = _length - currentLength;
    double percent = difference / currentLength / 2;

    //Translate get values
    double offsetX = _deltaX * percent;
    double offsetY = _deltaY * percent;

    //Stabilize dots
    _dotB->setX(_dotB->getX() -offsetX);
    _dotB->setY(_dotB->getY() -offsetY);
    _dotA->setX(_dotA->getX() + offsetX);
    _dotA->setY(_dotB->getY() + offsetY);
}

void Stick::Draw()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0 , SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_renderer, _dotA->getX() + _dotA->getRadius(), _dotA->getY() + _dotA->getRadius(),
                         _dotB->getX() + _dotB->getRadius(), _dotB->getY() + _dotB->getRadius());
}   