#include "output.h"

#include <stdexcept>

/////////////////////////////////////////////////////////////
// Constructor
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
// Destructor
/////////////////////////////////////////////////////////////

Output::~Output()
{
    if (activityFile.is_open())
        activityFile.close();

    if (activeNodesFile.is_open())
        activeNodesFile.close();
}
