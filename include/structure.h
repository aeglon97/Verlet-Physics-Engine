#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "dot.h"
#include "stick.h"

class Structure
{
public:
    ~Structure();

    //All child classes update and render the same way
    void Update(double deltaTime);
    void Draw();
    void setWindow(SDL_Window* window) { _window = window; }
    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }

    //Same declaration, different definitions

    //Same declaration, same definitions
    Dot* CreateDot(double radius);
    Stick* CreateStick(Dot* dotA, Dot* dotB);

    std::vector<Dot*> getDots() { return _dots; }
    
protected:
    //All child classes contain these elements
    std::vector<Dot*> _dots;
    std::vector<Stick*> _sticks; 
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};

//Cloth derives from structure
class Cloth : public Structure
{
public:
    Cloth(const int numPerRow, const int numPerColumn);
    ~Cloth();

    void Update(double deltaTime);
    void Draw();

    std::vector<std::vector<Dot*>> getMatrix() { return _matrix; }
    
    //Draw unique cloth shape
    void CreateMatrix(double radius);

private:
    const int _numPerRow;
    const int _numPerColumn;
    std::vector<std::vector<Dot*>> _matrix;
};

#endif