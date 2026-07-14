#include "output.h"

#include <stdexcept>

/////////////////////////////////////////////////////////////
//
// Constructor
//
/////////////////////////////////////////////////////////////

Output::Output()
{
    activityFile.open("ActivityInTime.txt");

    if (!activityFile.is_open())
        throw std::runtime_error("Cannot open ActivityInTime.txt");

    activeNodesFile.open("ActiveNodesInTime.txt");

    if (!activeNodesFile.is_open())
        throw std::runtime_error("Cannot open ActiveNodesInTime.txt");
}

/////////////////////////////////////////////////////////////
//
// Destructor
//
/////////////////////////////////////////////////////////////

Output::~Output()
{
    if (activityFile.is_open())
        activityFile.close();

    if (activeNodesFile.is_open())
        activeNodesFile.close();
}

/////////////////////////////////////////////////////////////
//
// Write global observables
//
/////////////////////////////////////////////////////////////

void Output::writeActivity(
    int t,
    double rho,
    double phiE,
    double phiI
)
{
    activityFile
        << t    << '\t'
        << rho  << '\t'
        << phiE << '\t'
        << phiI
        << '\n';
}

/////////////////////////////////////////////////////////////
//
// Write indices of active neurons
//
/////////////////////////////////////////////////////////////

void Output::writeActiveNodes(
    int t,
    const std::vector<int>& activeNodes
)
{
    activeNodesFile << t;

    for (int neuron : activeNodes)
        activeNodesFile << '\t' << neuron;

    activeNodesFile << '\n';
}
