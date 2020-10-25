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
    
    // _dots.push_back(CreateDot(10));
    // _dots.push_back(CreateDot(10));
    // _dots.push_back(CreateDot(10));
    // _dots.push_back(CreateDot(10));

    double leftX = (windowWidth / 15) - radius;
    double rightX = windowWidth - (windowWidth / 15) - radius;

    double upY = (windowHeight / 15) + radius;
    double downY = windowHeight - (windowHeight / 15) - radius;
    
    // Corner dots
    // _dots[0]->SetPosition(leftX, upY);
    // _dots[1]->SetPosition(leftX, downY);
    // _dots[2]->SetPosition(rightX, downY);
    // _dots[3]->SetPosition(rightX, upY);

    double stepRow = (rightX - leftX) / _numPerRow;
    double stepColumn = (downY - upY) / _numPerColumn;

    //Set up matrix of uninitialized dots
    std::vector<Dot*> row;

    for(int i = 0; i < _numPerRow; ++i) _matrix.push_back(std::vector<Dot*>(_numPerColumn));

    std::cout << _matrix.size() << std::endl;

    //push row into each new column
    // for (size_t j = 0; j < _numPerColumn; j++)
    // {
    //     _matrix.push_back(row);
    // }
    // int i = 0;
    // int j = 0;
    
    _matrix[0][0] = CreateDot(10);
    _matrix[0][1] = CreateDot(10);

    _matrix[0][0]->SetPosition(leftX, upY);
    _matrix[0][1]->SetPosition(rightX, upY);

    
    
    // _matrix[1][1]->SetPosition(rightX, upY);
    // _matrix[0][2]->SetPosition(leftX, downY);

    std::cout << _matrix[0][0]->getX() << std::endl;
    std::cout << _matrix[0][1]->getX() << std::endl;
    // std::cout << _matrix[0][2]->getX() << std::endl;
    // std::cout << _matrix[1][1]->getX() << std::endl;
    // Scan row by row
    // for(size_t y = upY; y < downY; y += stepColumn)
    // {   
    //     for(size_t x = leftX; x < rightX; x += stepRow)
    //     {
    //         j+=1;
    //         _matrix[j][i]->SetPosition(x, y);
    //         dot->SetPosition(x,y);
            
    //         std::cout << "Pinning dot" << std::endl;
    //         //Pin dots on first row
    //         if (y == upY) { _matrix[i][j]->Pin(true); }

    //         If not first in row, attach to left
    //         if (x != leftX)
    //         {
    //             // Dot* leftDot = _dots.back();
    //             // Stick* stick = CreateStick(dot, leftDot);
    //             // _sticks.push_back(stick);
    //             Stick* stick = CreateStick(_matrix[i][j], _matrix[i-1][j]);
    //             _sticks.push_back(stick);
    //         }

    //         //If not first in column, attach upward
    //         if(y != upY)
    //         {

    //         }

    //         _dots.push_back(dot);

    //         i == _numPerRow - 1 ? 0 : i += 1;
            
    //     }
    // }
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
        for (Stick *stick : _sticks) { stick->Update(); }
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

    for (Stick *stick : _sticks) { stick->Draw(); }
}

void Cloth::Update(double deltaTime)
{
    // int totalNum = _numPerColumn * _numPerRow;
    // for(int i = 0; i < totalNum; ++i)
    // {
    //     int row = floor(i / _numPerRow);
    //     int column = i % _numPerRow;

    //     _matrix[column][row]->Update(deltaTime);
    // }
}

Structure::~Structure()
{
    for (Dot* dot : _dots) { delete dot; }
    for (Stick* stick : _sticks) { delete stick; }
}
