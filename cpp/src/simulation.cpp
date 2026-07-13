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

/////////////////////////////////////////////////////////////
//
// Build an Erdős–Rényi directed random network.
//
// Each ordered neuron pair is connected independently
// with probability p.
//
// Excitatory neurons occupy the first N_E nodes,
// inhibitory neurons occupy the remaining nodes.
//
// This implements the structural connectivity of the
// model described in the manuscript.
//
/////////////////////////////////////////////////////////////

void Simulation::buildNetwork()
{
    int N_E = int(N * E);

    total_link = 0;

    for (int i = 0; i < N; i++)
    {
        adj[i].clear();

        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;

            double r = rand() / double(RAND_MAX);

            if (r < p)
            {
                Link link;

                link.target = j;

                link.lifetime = 0;

                if (i < N_E)
                    link.weight = W0E;
                else
                    link.weight = W0I;

                adj[i].push_back(link);

                total_link++;
            }
        }
    }
}
