#include <cstdlib>
#include <ctime>

#include "../include/simulation.h"

int main()
{
    srand(time(nullptr));

    Simulation simulation;

    simulation.buildNetwork();

    simulation.initializeNetwork();

    simulation.run();

    return 0;
}
