#include "structure.h"


//TODO: properly deallocate objects of derived classes


Cloth::Cloth(const int numPerRow, const int numPerColumn) :
    _numPerRow(numPerRow), _numPerColumn(numPerColumn)
{
    //Create matrix of dots

    //Connect all dots with lines
};

//Create matrix
void Cloth::InitializeDots(double radius)
{
    const int windowWidth = SDL_GetWindowSurface(_window)->w;
    const int windowHeight = SDL_GetWindowSurface(_window)->h;

    double leftX = (windowWidth / 15) - radius;
    double rightX = windowWidth - (windowWidth / 15) - radius;

    double upY = (windowHeight / 15) + radius;
    double downY = windowHeight - (windowHeight / 15) - radius;

    double stepRow = (rightX - leftX) / _numPerRow;
    double stepColumn = (downY - upY) / _numPerColumn;

    //Set up matrix of uninitialized dots

    //Push rows into columns
    for(int i = 0; i < _numPerRow; ++i) _matrix.push_back(std::vector<Dot*>(_numPerColumn));
    
    //Row by row scan
    int j = 0;
    
    for(size_t y = upY; y < downY; y += stepColumn)
    {   
        int i = 0;
        for(size_t x = leftX; x < rightX - radius * 2; x += stepRow)
        {
            Dot *currentDot = CreateDot(radius);

            _matrix[j][i] = currentDot;
            _matrix[j][i]->SetPosition(x,y);
            
            //Pin dots on first row
            if (j == 0) { currentDot->Pin(true); }

            // If not first in row, connect to left
            if (x != leftX)
            {
                Dot* leftDot = _matrix[j][i-1];
                std::cout << "left dot x: " << leftDot->getX() << std::endl;
                Stick* stick = CreateStick(currentDot, leftDot);
                _sticks.push_back(stick);
            }

            //If not first in column, connect upward
            if(y != upY)
            {
                Dot *upDot = _matrix[j-1][i];
                Stick* stick = CreateStick(currentDot, upDot);
                _sticks.push_back(stick);
            }
            std::cout << "created row" << std::endl;
            i += 1;
        }
        j += 1;
    }
}

//Generate new dot with predefined properties
 Dot* Structure::CreateDot(double radius)
 {
    Dot *dot = new Dot(radius);
    dot->setWindow(_window);
    dot->setRenderer(_renderer);
    dot->AssignTexture("../img/dot.png");
    return dot;
 }

//Generate new stick with predefined properties
Stick* Structure::CreateStick(Dot* dotA, Dot* dotB)
{
    Stick *stick = new Stick(dotA, dotB);
    stick->setWindow(_window);
    stick->setRenderer(_renderer);
    std::cout << "created stick (from Structure method)" << std::endl;
    return stick;
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

     //Add point rigidity
    for(int i = 0; i < 5; ++i)
    {
        //Update sticks
        for (Stick *stick : _sticks){ stick->Update(); }
        //Constrain points
        // for (Dot* dot : _dots) { dot->ApplyConstraints(); }
    }
}

void Structure::Draw()
{
    //Draw dots
    for (Dot* dot : _dots) { dot->Draw(); }

    // Draw sticks
    for (Stick* stick : _sticks) { stick->Draw(); }
}

void Cloth::Draw()
{
    int totalNum = _numPerColumn * _numPerRow;
    for(int i = 0; i < totalNum; ++i)
    {
        int row = floor(i / _numPerRow);
        int column = i % _numPerRow;
        if (_matrix[row][column]) _matrix[row][column]->Draw();
    }
    for (Stick *stick : _sticks) { if(stick) stick->Draw(); }
}

void Cloth::Update(double deltaTime)
{
    int totalNum = _numPerColumn * _numPerRow;
    for(int i = 0; i < totalNum; ++i)
    {
        int row = floor(i / _numPerRow);
        int column = i % _numPerRow;
        if(_matrix[row][column])
         _matrix[row][column]->Update(deltaTime);
    }

    for(Stick *stick : _sticks) { if(stick) stick->Update();}
}

Structure::~Structure()
{
    for (Dot* dot : _dots) { delete dot; }
    for (Stick* stick : _sticks) { delete stick; }
}
