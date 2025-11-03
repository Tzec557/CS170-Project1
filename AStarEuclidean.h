#ifndef ASTAR_EUCLIDEAN_H
#define ASTAR_EUCLIDEAN_H

#include "Problem.h"
#include <memory>

using namespace std;

shared_ptr<Node> aStarEuclidean(const Problem& problem);

#endif
