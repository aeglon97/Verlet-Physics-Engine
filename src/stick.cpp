#include "stick.h"
#include <cmath>

Stick::Stick(Dot* dotA, Dot* dotB) :
    _dotA(dotA), _dotB(dotB)
{
    _length = InitializeLength();
}  

double Stick::InitializeLength()
{
    //Pythagorean distance 
    double deltaX = _dotB->getX() - _dotA->getX();
    double deltaY = _dotB->getY() - _dotA->getY();

    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

void Stick::Update()
{
    //Calculate current length, compare to actual length
    double deltaX = _dotB->getX() - _dotA->getX();
    double deltaY = _dotB->getY() - _dotA->getY();
    double currentLength = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

    double difference = _length - currentLength;
    double percent = difference / currentLength / 2;

    //Offset values
    double offsetX = deltaX * percent;
    double offsetY = deltaY * percent;

    //Restabilize dots to stick length
    if(!_dotB->Pinned())
    {
        _dotB->setX(_dotB->getX() + offsetX);
        _dotB->setY(_dotB->getY() + offsetY);
    }
    
    if(!_dotA->Pinned())
    {
        _dotA->setX(_dotA->getX() - offsetX);
        _dotA->setY(_dotA->getY() - offsetY);
    }
}

void Stick::Draw()
{
    if(!_hidden)
    {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255 , SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(_renderer, _dotA->getCenterX(), _dotA->getCenterY(),
                        _dotB->getCenterX(), _dotB->getCenterY());
    }
}