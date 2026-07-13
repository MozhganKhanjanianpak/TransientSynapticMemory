#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

/////////////////////////////////////////////////////////////
//
// Link
//
// Represents a directed synaptic connection.
//
// weight:
//      Synaptic weight
//
// lifetime:
//      Remaining active lifetime of the synapse.
//
/////////////////////////////////////////////////////////////

struct Link
{
    int target;

    double weight;

    int lifetime;
};

#endif
