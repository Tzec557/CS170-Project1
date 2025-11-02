#ifndef UNIFORMCOST_H
#define UNIFORMCOST_H

#include "Problem.h"
#include <memory>

using namespace std;

shared_ptr<Node> uniformCostSearch(const Problem& problem);

#endif
