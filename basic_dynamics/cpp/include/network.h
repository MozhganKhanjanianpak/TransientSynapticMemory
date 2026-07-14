#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

/////////////////////////////////////////////////////////////
//
// Link
//
// Represents a directed synaptic connection between two
// neurons in the network.
//
// target:
//      Index of the postsynaptic neuron.
//
// weight:
//      Synaptic efficacy
//      (+ for excitatory, - for inhibitory).
//
// lifetime:
//      Remaining active duration (simulation steps)
//      before the synapse becomes inactive.
//
/////////////////////////////////////////////////////////////

struct Link
{
    int target;

    double weight;

    int lifetime;
};

#endif
