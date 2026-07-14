#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <vector>

class Output
{
public:

    Output();

    ~Output();

    void writeActivity(
        int t,
        double rho,
        double phiE,
        double phiI
    );

    void writeActiveNodes(
        int t,
        const std::vector<int>& activeNodes
    );

private:

    std::ofstream activityFile;

    std::ofstream activeNodesFile;
};

#endif
