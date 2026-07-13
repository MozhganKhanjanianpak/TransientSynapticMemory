#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../include/simulation.h"

using namespace std;

//--------------------------------------------------
int main() {

	srand(time(NULL));
	
	Simulation simulation;
	
	simulation.buildNetwork();

	simulation.initializeNetwork();

	simulation.run();


	//---------------------------------------------------
	
	ofstream output("ActivityInTime.txt");
	ofstream output_active_nodes_at_t("ActiveNodesInTime.txt");

	int N_E = N * E;
	int t = 0;	


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


	return 0;
}
