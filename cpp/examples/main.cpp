#include <cstdlib>
#include <ctime>

#include "../include/simulation.h"

int main()
{
    srand(time(nullptr));

    Simulation simulation;

    simulation.run();

    return 0;
}
