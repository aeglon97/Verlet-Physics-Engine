#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "dot.h"
#include "stick.h"

class Structure
{
public:
    //All child classes update and render the same way
    void Update(double deltaTime);
    void Draw();
    void setWindow(SDL_Window* window) { _window = window; }
    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }

    //Gives all child classes ability to create their own forms
    virtual void InitializeDots() = 0;
    virtual void InitializeSticks() = 0;

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
    void Update(double deltaTime) { Structure::Update(deltaTime); }
    void Draw() { Structure::Draw(); }
    
    //Draw unique cloth shape
    void InitializeDots() override;
    void InitializeSticks() override;

private:
    
    const int _numPerRow;
    const int _numPerColumn;
};

#endif