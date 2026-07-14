#include <cstdlib>
#include <ctime>

#include "simulation.h"

int main()
{
    srand(time(nullptr));

    Simulation simulation;

    simulation.run();

    return 0;
}
