#include "structure.h"

//TODO: properly deallocate objects of derived classes


Cloth::Cloth(const int numPerRow, const int numPerColumn) :
    _numPerRow(numPerRow), _numPerColumn(numPerColumn)
{
    //Create matrix of dots
    
    //Connect all dots with lines
};

//
void Cloth::InitializeDots()
{
    const int windowWidth = SDL_GetWindowSurface(_window)->w;
    const int windowHeight = SDL_GetWindowSurface(_window)->h;

    _dots.push_back(new Dot());
    _dots.push_back(new Dot());
    _dots.push_back(new Dot());
    _dots.push_back(new Dot());


    double leftX = (windowWidth / 15) - _dots[0]->getRadius();
    double rightX = windowWidth - (windowWidth / 15) - _dots[0]->getRadius();

    double upY = (windowHeight / 15) + _dots[0]->getRadius();
    double downY = windowHeight - (windowHeight / 15) - _dots[0]->getRadius();
    
    //Corner dots
    _dots[0]->SetPosition(leftX, upY);
    _dots[1]->SetPosition(leftX, downY);
    _dots[2]->SetPosition(rightX, downY);
    _dots[3]->SetPosition(rightX, upY);


    double stepRow = (rightX - leftX) / _numPerRow;
    double stepColumn = (downY - upY) / _numPerColumn;
    //Matrix dots

    //Scan row by row
    for(size_t y = upY; y < downY; y += stepColumn)
    {   
        for(size_t x = leftX; x < rightX; x += stepRow)
        {
            Dot* dot = new Dot();
            dot->SetPosition(x,y);
            
            
            //If at top, pin
            if (y == upY) { dot->Pin(true); }

            //If not first in row, attach to left
            if (x != leftX)
            {
                Dot* leftDot = _dots.back();
                Stick* stick = new Stick(dot, leftDot);
            }

            //If 
            // Stick* stick = new Stick()
            


            _dots.push_back(dot);
        }
    }
        //Pin dots on first row
}



void Cloth::InitializeSticks()
{

}

void Structure::Update(double deltaTime)
{
    // for (Dot* dot : _dots)
    // {
    //     dot->Update(deltaTime);
    //     // dot->ApplyConstraints();
    // }

    //  //Add point rigidity
    // for(int i = 0; i < 5; ++i)
    // {
    //     //Update sticks
    //     for (Stick *stick : _sticks) { stick->Update(); }
    //     //Constrain points
    //     // for (Dot* dot : _dots) { dot->ApplyConstraints(); }
    // }
}

void Structure::Draw()
{
    //Draw dots
    for (Dot* dot : _dots) { dot->Draw(); }

    //Draw sticks
    // for (Stick* stick : _sticks) { stick->Draw(); }
}

