#include "output.h"
#include <stdexcept>
#include "output.h"
#include <stdexcept>
#include <string>

/////////////////////////////////////////////////////////////
//
// Constructor
//
/////////////////////////////////////////////////////////////

Output::Output()
{/*
    activityFile.open("ActivityInTime.txt");

    if(!activityFile.is_open())
        throw std::runtime_error("Cannot open ActivityInTime.txt");

    activeNodesFile.open("ActiveNodesInTime.txt");

    if(!activeNodesFile.is_open())
        throw std::runtime_error("Cannot open ActiveNodesInTime.txt");

    potentialFile.open("PotentialReactivation.txt");

    if(!potentialFile.is_open())
        throw std::runtime_error("Cannot open PotentialReactivation.txt");

    ghostNodesFile.open("GhostNodesInTau.txt");

    if(!ghostNodesFile.is_open())
        throw std::runtime_error("Cannot open GhostNodesInTau.txt");

    activeNodesTauFile.open("ActiveNodesInTau.txt");

    if(!activeNodesTauFile.is_open())
        throw std::runtime_error("Cannot open ActiveNodesInTau.txt");*/
}

/////////////////////////////////////////////////////////////
//
// Destructor
//
/////////////////////////////////////////////////////////////

Output::~Output()
{
    closeFiles();
}

/////////////////////////////////////////////////////////////
//
// Close all output files
//
/////////////////////////////////////////////////////////////

void Output::closeFiles()
{
    if(activityFile.is_open())
        activityFile.close();

    if(activeNodesFile.is_open())
        activeNodesFile.close();

    if(potentialFile.is_open())
        potentialFile.close();

    if(ghostNodesFile.is_open())
        ghostNodesFile.close();

    if(activeNodesTauFile.is_open())
        activeNodesTauFile.close();
}

/////////////////////////////////////////////////////////////
//
// Open output files for one realization
//
/////////////////////////////////////////////////////////////

void Output::openFiles(int realizationID)
{
    closeFiles();

    activityFile.open(
        "ActivityInTime_" +
        std::to_string(realizationID) +
        ".txt"
    );

    activeNodesFile.open(
        "ActiveNodesInTime_" +
        std::to_string(realizationID) +
        ".txt"
    );

    potentialFile.open(
        "PotentialReactivation_" +
        std::to_string(realizationID) +
        ".txt"
    );

    ghostNodesFile.open(
        "GhostNodesInTau_" +
        std::to_string(realizationID) +
        ".txt"
    );

    activeNodesTauFile.open(
        "ActiveNodesInTau_" +
        std::to_string(realizationID) +
        ".txt"
    );

    if(!activityFile.is_open())
        throw std::runtime_error("Cannot open ActivityInTime file.");

    if(!activeNodesFile.is_open())
        throw std::runtime_error("Cannot open ActiveNodesInTime file.");

    if(!potentialFile.is_open())
        throw std::runtime_error("Cannot open PotentialReactivation file.");

    if(!ghostNodesFile.is_open())
        throw std::runtime_error("Cannot open GhostNodesInTau file.");

    if(!activeNodesTauFile.is_open())
        throw std::runtime_error("Cannot open ActiveNodesInTau file.");
}

/////////////////////////////////////////////////////////////
//
// Write activity
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
        << t << '\t'
        << rho << '\t'
        << phiE << '\t'
        << phiI
        << '\n';
}

/////////////////////////////////////////////////////////////
//
// Write active neurons
//
/////////////////////////////////////////////////////////////

void Output::writeActiveNodes(
    int t,
    const std::vector<int>& activeNodes
)
{
    activeNodesFile << t;

    for(int neuron : activeNodes)
        activeNodesFile << '\t' << neuron;

    activeNodesFile << '\n';
}

/////////////////////////////////////////////////////////////
//
// Write potential reactivation
//
/////////////////////////////////////////////////////////////

void Output::writePotential(
    int tau,
    const std::vector<double>& potentials
)
{
    potentialFile << tau;

    for(double value : potentials)
        potentialFile << '\t' << value;

    potentialFile << '\n';
}

/////////////////////////////////////////////////////////////
//
// Write ghost neurons
//
/////////////////////////////////////////////////////////////

void Output::writeGhostNodes(
    int tau,
    const std::vector<int>& ghostNodes
)
{
    ghostNodesFile << tau;

    for(int neuron : ghostNodes)
        ghostNodesFile << '\t' << neuron;

    ghostNodesFile << '\n';
}

/////////////////////////////////////////////////////////////
//
// Write active neurons at tau
//
/////////////////////////////////////////////////////////////

void Output::writeActiveNodesTau(
    int tau,
    const std::vector<int>& activeNodesTau
)
{
    activeNodesTauFile << tau;

    for(int neuron : activeNodesTau)
        activeNodesTauFile << '\t' << neuron;

    activeNodesTauFile << '\n';
}

