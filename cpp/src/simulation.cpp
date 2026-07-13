#include "simulation.h"

Simulation::Simulation()
{
    total_link = 0;

    for(int i=0;i<N;i++)
    {
        node_state[i]=0;
        node_input[i]=0;
    }
}
