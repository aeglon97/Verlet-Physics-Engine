#include "structure.h"


//TODO: properly deallocate objects of derived classes


Cloth::Cloth(const int numPerRow, const int numPerColumn) :
    _numPerRow(numPerRow), _numPerColumn(numPerColumn)
{
};

Cloth::~Cloth()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    for (auto &vec : _matrix)
    {
        for(auto &dot : vec)
        {
            SDL_DestroyTexture(dot->getTexture());
            delete dot;
        }
    }
    for (Stick* stick : _sticks) delete stick;
}

//Create matrix
void Cloth::CreateMatrix(double radius)
{
    const int windowWidth = SDL_GetWindowSurface(_window)->w;
    const int windowHeight = SDL_GetWindowSurface(_window)->h;

    //Push rows into columns
    for(int i = 0; i < _numPerRow; ++i) _matrix.push_back(std::vector<Dot*>(_numPerColumn));

    double leftX = (windowWidth / 15) - radius;
    double rightX = windowWidth - (windowWidth / 15) - radius;

    double upY = (windowHeight / 15) + radius;
    double downY = windowHeight - (windowHeight / 15) - radius;

    double stepRow = (rightX - leftX) / _numPerRow;
    std::cout << "steprow: " << stepRow << std::endl;
    double stepColumn = (downY - upY) / _numPerColumn;
    std::cout << "stepcolumn: " << stepColumn << std::endl;
    
    //Row by row scan
    int j = 0;
    
    for(size_t y = upY; y < downY; y += stepColumn)
    {   
        int i = 0;
        for(size_t x = leftX; x < rightX - (radius * 2); x += stepRow)
        {
            int randY = rand() % _numPerColumn;

            Dot *currentDot = CreateDot(radius);

            _matrix[j][i] = currentDot;
            currentDot->SetPosition(x,y);
            std::cout << "-------------\nAt dot " << j << ", " << i << std::endl;
            // currentDot->Hide(true);
            // std::cout << currentDot->getX() << " ";
            
            //Pin dots on first row
            if (j == 0) { currentDot->Pin(true); }
            // If dot not first in row, connect to left dot
            if (x != leftX)
            {
                Dot* leftDot = _matrix[j][i-1];
                Stick* stick = CreateStick(currentDot, leftDot);
                _sticks.push_back(stick);
                std::cout << "Created left stick" << std::endl;
            }

            //If not first in column, connect upward
            if(y != upY)
            {
                Dot *upDot = _matrix[j-1][i];
                Stick* stick = CreateStick(currentDot, upDot);
                _sticks.push_back(stick);
                std::cout << "Created up stick" << std::endl;
            }
            i ++;
            std::cout << "jumped to stick in column " << i << std::endl;
        }
        j ++;
        std::cout << "jumped to stick in row " << j << std::endl;
    }
}

//Generate new dot with predefined properties
 Dot* Structure::CreateDot(double radius)
 {
    Dot *dot = new Dot(radius);
    dot->setWindow(_window);
    dot->setRenderer(_renderer);
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
        int row = i / _numPerRow;
        int column = i % _numPerRow;
        if (_matrix[row][column]) _matrix[row][column]->Draw();
    }
    for (Stick *stick : _sticks) { if(stick) stick->Draw(); }
}

void Cloth::Update(double deltaTime)
{

    //Update dots
    int totalNum = _numPerColumn * _numPerRow;
    for(int i = 0; i < totalNum; ++i)
    {
        int row = floor(i / _numPerRow);
        int column = i % _numPerRow;
        if(_matrix[row][column])
         _matrix[row][column]->Update(deltaTime);
    }

    //Update sticks
    for(Stick *stick : _sticks) { if(stick) stick->Update();}
}

Structure::~Structure()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    
    for (Dot* dot : _dots) {
        SDL_DestroyTexture(dot->getTexture());
        delete dot;
    }
    for (Stick* stick : _sticks) { delete stick; }
    delete this;
}
