#include "simulation.h"

#include <algorithm>
#include <cstdlib>

/////////////////////////////////////////////////////////////
//
// Constructor
//
/////////////////////////////////////////////////////////////

Simulation::Simulation()
{
    N_E = static_cast<int>(N * E);

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

void Simulation::buildNetwork()
{
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
// Random initial activation
//
/////////////////////////////////////////////////////////////

void Simulation::initializeNetwork()
{
    int N_E_0 = static_cast<int>(N_E * eta);
    int N_I_0 = static_cast<int>((N - N_E) * eta);

    //------------------------------------------------------
    // Excitatory neurons
    //------------------------------------------------------

    int counter = 0;

    while (counter < N_E_0)
    {
        int neuron = rand() % N_E;

        if (node_state[neuron] == 0)
        {
            node_state[neuron] = 1;
            counter++;
        }
    }

    //------------------------------------------------------
    // Inhibitory neurons
    //------------------------------------------------------

    counter = 0;

    while (counter < N_I_0)
    {
        int neuron = rand() % (N - N_E);

        if (node_state[N - neuron - 1] == 0)
        {
            node_state[N - neuron - 1] = 1;
            counter++;
        }
    }
}

/////////////////////////////////////////////////////////////
//
// STEP 3
//
// Update synaptic lifetimes
//
/////////////////////////////////////////////////////////////

void Simulation::updateLinks()
{
    for (int i = 0; i < N; i++)
    {
        int Tmax = (i < N_E) ? TE : TI;

        for (auto& link : adj[i])
        {
            int term1 =
                H(link.lifetime) *
                (link.lifetime - 1);

            int term2 =
                (1 - H(link.lifetime)) *
                Tmax *
                node_state[i];

            link.lifetime =
                term1 + term2;
        }
    }
}

/////////////////////////////////////////////////////////////
//
// STEP 4
//
// Compute synaptic inputs
//
/////////////////////////////////////////////////////////////

void Simulation::computeInputs()
{
    std::fill(node_input,
              node_input + N,
              0);

    for (int i = 0; i < N; i++)
    {
        for (auto& link : adj[i])
        {
            node_input[link.target] +=
                H(link.lifetime) *
                link.weight;
        }
    }
}

/////////////////////////////////////////////////////////////
//
// STEP 5
//
// Update neuronal states
//
/////////////////////////////////////////////////////////////

void Simulation::updateNodes()
{
    for (int i = 0; i < N; i++)
    {
        int term1 =
            H(node_input[i] - D);

        int term2 = 0;

        /*
        // Continuous external drive

        double r =
            rand() / double(RAND_MAX);

        term2 =
            (1 - H(node_input[i] - D))
            * H(eta - r);
        */

        node_state[i] =
            term1 + term2;
    }
}

/////////////////////////////////////////////////////////////
//
// STEP 6
//
// Run simulation
//
/////////////////////////////////////////////////////////////

void Simulation::run()
{
    //------------------------------------------------------
    // Build network
    //------------------------------------------------------

    buildNetwork();

    //------------------------------------------------------
    // Initial activation
    //------------------------------------------------------

    initializeNetwork();

    //------------------------------------------------------
    // Output at t = 0
    //------------------------------------------------------

    {
        int active = 0;

        for (int i = 0; i < N; i++)
            active += node_state[i];

        output.writeActivity(
            0,
            active / double(N),
            0.0,
            0.0
        );

        std::vector<int> activeNodes;

        for (int i = 0; i < N; i++)
        {
            if (node_state[i] == 1)
                activeNodes.push_back(i);
        }

        output.writeActiveNodes(
            0,
            activeNodes
        );
    }

    //------------------------------------------------------
    // Main dynamics
    //------------------------------------------------------

    for (int t = 1; t <= tmax; t++)
    {
        //----------------------------------------------
        // Update network
        //----------------------------------------------

        updateLinks();

        computeInputs();

        updateNodes();

        //----------------------------------------------
        // Compute global observables
        //----------------------------------------------

        int active = 0;

        for (int i = 0; i < N; i++)
            active += node_state[i];

        int active_link_E = 0;
        int active_link_I = 0;

        for (int i = 0; i < N; i++)
        {
            for (auto& link : adj[i])
            {
                if (i < N_E)
                    active_link_E += H(link.lifetime);
                else
                    active_link_I += H(link.lifetime);
            }
        }

        double rho =
            active / double(N);

        double phiE =
            active_link_E / double(total_link);

        double phiI =
            active_link_I / double(total_link);

        //----------------------------------------------
        // Write activity
        //----------------------------------------------

        output.writeActivity(
            t,
            rho,
            phiE,
            phiI
        );

        //----------------------------------------------
        // Store active neurons
        //----------------------------------------------

        std::vector<int> activeNodes;

        for (int i = 0; i < N; i++)
        {
            if (node_state[i] == 1)
                activeNodes.push_back(i);
        }

        output.writeActiveNodes(
            t,
            activeNodes
        );
    }
}
