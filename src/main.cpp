#include <iostream>
#include "simulator.h"

int main()
{
    Simulator simulator(1000, 680);
    simulator.Update();
    simulator.Draw();
    return 0;
}

