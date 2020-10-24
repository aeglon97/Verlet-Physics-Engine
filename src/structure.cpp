#include "structure.h"

//TODO: properly deallocate objects of derived classes


Cloth::Cloth(const int width, const int height, SDL_Window* window, SDL_Renderer* renderer) :
    _width(width), _height(width)
{
    //Create matrix of dots
    
    //Connect all dots with lines
};

//
void Cloth::InitializeDots()
{
    _dots.push_back(new Dot(_window, _renderer));
}



void Cloth::InitializeSticks()
{

}

void Structure::Update(double deltaTime)
{
    for (Dot* dot : _dots)
    {
        dot->Update(deltaTime);
        // dot->ApplyConstraints();
    }

     //Add point rigidity
    for(int i = 0; i < 5; ++i)
    {
        //Update sticks
        for (Stick *stick : _sticks) { stick->Update(); }
        //Constrain points
        // for (Dot* dot : _dots) { dot->ApplyConstraints(); }
    }
}

void Structure::Draw()
{
    //Draw dots
    for (Dot* dot : _dots) { dot->Draw(); }

    //Draw sticks
    // for (Stick* stick : _sticks) { stick->Draw(); }
}

