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
    for (int t = 1; t <= tmax; t++) {
		//--------------------------------------------------
		// (1) Update link lifetime
		//--------------------------------------------------
		for (int i = 0; i < N; i++) {
			int Tmax = (i < N_E) ? TE : TI;
			for (auto &link : adj[i]) {
				int term1 = H(link.lifetime) * (link.lifetime - 1);
				int term2 = (1 - H(link.lifetime)) * Tmax * node_state[i];
				link.lifetime = (term1 + term2);
			}
		}

		//--------------------------------------------------
		// (2) Compute inputs
		//--------------------------------------------------
		for (int i = 0; i < N; i++)
			node_input[i] = 0;

		for (int i = 0; i < N; i++) {
			for (auto &link : adj[i]) {
				node_input[link.target] += H(link.lifetime) * link.weight;
			}
		}

		//--------------------------------------------------
		// (3) Update node states
		//--------------------------------------------------
		for (int i = 0; i < N; i++) {
			int term1 = H(node_input[i] - D);
			int term2 = 0;

			/*/ activation because of external input at each time step
			double r = rand()/double(RAND_MAX);
			term2 = (1- H(node_input[i] - D)) * H(eta-r);*/

			node_state[i] = term1 + term2;
		}

		//--------------------------------------------------
		// (4) Output activity
		//--------------------------------------------------
		active = 0;
		for (int i = 0; i < N; i++)
			active += node_state[i];

		// Rho at t
		output << t << "\t" << active / N << "\t";

		// Phi at t
		int active_link_E = 0;
		int active_link_I = 0;
		for (int i = 0; i < N; i++) {
			for (auto &link : adj[i]) {
				if (i < N_E)
					active_link_E += H(link.lifetime);
				else
					active_link_I += H(link.lifetime);
			}
		}
		output << active_link_E/double(total_link) << "\t" << active_link_I/double(total_link) << endl;

		// output active nodes at t
		output_active_nodes_at_t << t << "\t";
		for (int i=0 ; i<N ; i++)
			if (node_state[i]==1)
				output_active_nodes_at_t << i << "\t";
		output_active_nodes_at_t << endl;
	}
}

