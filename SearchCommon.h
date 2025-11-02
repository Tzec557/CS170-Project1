#ifndef SEARCHCOMMON_H
#define SEARCHCOMMON_H

#include "Problem.h"
#include <memory>

using namespace std;

// Return a pointer to the goal Node if found, else nullptr
shared_ptr<Node> uniformCostSearch(const Problem& problem);
shared_ptr<Node> aStarMisplaced(const Problem& problem);

#endif
