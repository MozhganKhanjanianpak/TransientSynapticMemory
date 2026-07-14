#include "output.h"

Output::Output()
{
    activityFile.open("ActivityInTime.txt");

    activeNodesFile.open("ActiveNodesInTime.txt");
}

Output::~Output()
{
    activityFile.close();

    activeNodesFile.close();
}
