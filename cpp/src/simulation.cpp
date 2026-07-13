#include "simulation.h"
#include <algorithm>

Simulation::Simulation()
{
    total_link = 0;

    std::fill(node_state, node_state + N, 0);
    std::fill(node_input, node_input + N, 0);
}

/////////////////////////////////////////////////////////////
//
// STEP 1
//
// Build network topology
//
/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////
//
// STEP 2
//
// Initialize neuronal activity
//
// Randomly activates a fraction eta of excitatory
// and inhibitory neurons at t = 0.
//
/////////////////////////////////////////////////////////////

void Simulation::initializeNetwork()
{
    int N_E = int(N * E);

    int N_E_0 = int(N_E * eta);
    int N_I_0 = int((N - N_E) * eta);

    //--------------------------------------------------
    // Random activation of excitatory neurons
    //--------------------------------------------------

    int counter = 0;

    while(counter < N_E_0)
    {
        int neuron = rand() % N_E;

        if(node_state[neuron]==0)
        {
            node_state[neuron]=1;
            counter++;
        }
    }

    //--------------------------------------------------
    // Random activation of inhibitory neurons
    //--------------------------------------------------

    counter = 0;

    while(counter < N_I_0)
    {
        int neuron = rand() % (N-N_E);

        if(node_state[N-neuron-1]==0)
        {
            node_state[N-neuron-1]=1;
            counter++;
        }
    }
}

/////////////////////////////////////////////////////////////
//
// STEP 3
//
// Main simulation loop
//
/////////////////////////////////////////////////////////////

void Simulation::run()
{

}

