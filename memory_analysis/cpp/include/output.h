#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <vector>

/////////////////////////////////////////////////////////////
//
// Output
//
// Handles writing simulation results to disk.
//
/////////////////////////////////////////////////////////////

class Output
{
public:

    /////////////////////////////////////////////////////////////
    // Constructor / Destructor
    /////////////////////////////////////////////////////////////

    Output();

    ~Output();

    /////////////////////////////////////////////////////////////
    //
    // Open / Close output files
    //
    /////////////////////////////////////////////////////////////

    void openFiles(int realizationID);

    void closeFiles();

    /////////////////////////////////////////////////////////////
    // Write global observables
    /////////////////////////////////////////////////////////////

    void writeActivity(
        int t,
        double rho,
        double phiE,
        double phiI
    );

    /////////////////////////////////////////////////////////////
    // Write indices of active neurons
    /////////////////////////////////////////////////////////////

    void writeActiveNodes(
        int t,
        const std::vector<int>& activeNodes
    );


    void writePotential(
        int tau,
        const std::vector<double>& potentials
    );

    void writeGhostNodes(
        int tau,
        const std::vector<int>& ghostNodes
    );

    void writeActiveNodesTau(
        int tau,
        const std::vector<int>& activeNodesTau
    );

private:

    /////////////////////////////////////////////////////////////
    // Output streams
    /////////////////////////////////////////////////////////////

    std::ofstream activityFile;

    std::ofstream activeNodesFile;

    std::ofstream potentialFile;

    std::ofstream ghostNodesFile;

    std::ofstream activeNodesTauFile;
};

#endif
