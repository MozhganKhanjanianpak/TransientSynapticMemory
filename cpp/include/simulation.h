#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "network.h"
#include "parameters.h"
#include "output.h"

class Simulation
{
public:

    Simulation();

    void buildNetwork();

    void initializeNetwork();

    void updateLinks();

    void computeInputs();

    void updateNodes();

    void writeOutput(int t);

    void run();

private:

    // Network
    std::vector<Link> adj[N];

    // Neuron states
    int node_state[N];
    int node_input[N];

    // Statistics
    int total_link;

};

#endif
