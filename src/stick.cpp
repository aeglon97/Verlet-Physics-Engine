#include "stick.h"
#include <cmath>

Stick::Stick(Dot* dotA, Dot* dotB, SDL_Window* window, SDL_Renderer* renderer): _dotA(dotA),
_dotB(dotB), _length(InitializeLength()), _window(window), _renderer(renderer)
{
    
}

double Stick::InitializeLength()
{
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
    _dotB->setX(_dotB->getX() +offsetX);
    _dotB->setY(_dotB->getY() +offsetY);
    _dotA->setX(_dotA->getX() - offsetX);
    _dotA->setY(_dotA->getY() - offsetY);
}

void Stick::Draw()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0 , SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_renderer, _dotA->getCenterX(), _dotA->getCenterY(),
                        _dotB->getCenterX(), _dotB->getCenterY());
}