#include <iostream>
#include "simulator.h"

#define SCREENWIDTH 1000
#define SCREENHEIGHT 680

int main()
{
    Simulator simulator(SCREENWIDTH, SCREENHEIGHT);
    simulator.Loop();
    return 0;
}

