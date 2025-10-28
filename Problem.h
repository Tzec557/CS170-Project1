#ifndef PROBLEM_H
#define PROBLEM_H

#include "Node.h"
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

class Problem {
public:
    vector<int> initial;
    vector<int> goal;

    Problem(vector<int> initial, vector<int> goal);
    bool goalTest(const vector<int>& state) const;
    vector<shared_ptr<Node>> getNeighbors(shared_ptr<Node> node) const;

private:
    bool canMove(int blankIndex, int direction) const;
    vector<int> move(const vector<int>& state, int direction) const;
};

#endif