#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../include/simulation.h"

using namespace std;

//--------------------------------------------------
int main() {

	Simulation simulation;

	ofstream output("ActivityInTime.txt");
	ofstream output_active_nodes_at_t("ActiveNodesInTime.txt");

	srand(time(NULL));

	int N_E = N * E;
	int t = 0;


	
	simulation.buildNetwork();


	

	//--------------------------------------------------
	// Initial activation
	//--------------------------------------------------
	// Initial eta as a uniform random number
	int N_E_0 = N_E * eta;
	int N_I_0 = (N - N_E) * eta;
	
	// Random activation -------------------------------
	// Excitatory nodes
	int N_E_0_counter = 0;
	while (N_E_0_counter < N_E_0) {
		int rand_E_node = rand()%N_E;
		if (node_state[rand_E_node] == 0) {
			node_state[rand_E_node] = 1;
			N_E_0_counter++;
		}
	}

	// Inhibitory nodes
	int N_I_0_counter = 0;
	while (N_I_0_counter < N_I_0)
	{
		int rand_I_node = rand()%(N - N_E);
		if (node_state[N - rand_I_node - 1] == 0) {
			node_state[N - rand_I_node - 1] = 1;
			N_I_0_counter++;
		}
	}//*/


	// Output at t=0 ----------------------------------
	double active = 0;
	for (int i = 0; i < N; i++) {
		active += node_state[i];
	}

	output << "0\t" << active / N << "\t0" << "\t0" << endl; // time-Rho-PhiE-PhiI

	output_active_nodes_at_t << "0\t";
	for (int i=0 ; i<N ; i++)
		if (node_state[i]==1)
			output_active_nodes_at_t << i << "\t";
	output_active_nodes_at_t << endl;

	//--------------------------------------------------
	// Dynamics
	//--------------------------------------------------
	for (t = 1; t <= tmax; t++) {
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
	return 0;
}
