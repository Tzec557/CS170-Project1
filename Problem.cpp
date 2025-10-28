#include "Problem.h"
#include <algorithm>

// Directions: 0 = up, 1 = down, 2 = left, 3 = right
Problem::Problem(vector<int> initial, vector<int> goal)
    : initial(initial), goal(goal) {
        assert(initial.size() == 9 && "Initial state must have 9 elements");
        assert(goal.size() == 9 && "Goal state must have 9 elements");
    }

bool Problem::goalTest(const vector<int>& state) const {
    return state == goal;
}

vector<shared_ptr<Node>> Problem::getNeighbors(shared_ptr<Node> node) const {
    vector<shared_ptr<Node>> neighbors;

    int blankIndex = find(node->state.begin(), node->state.end(), 0) - node->state.begin();

     for (int dir = 0; dir < 4; dir++) {
        if (canMove(blankIndex, dir)) {
            vector<int> newState = move(node->state, dir);
            neighbors.push_back(make_shared<Node>(newState, node, node->g + 1));
        }
    }
    return neighbors;
}

bool Problem::canMove(int blank, int dir) const {
    if (dir == 0 && blank >= 3) return true;      // up
    if (dir == 1 && blank <= 5) return true;      // down
    if (dir == 2 && blank % 3 != 0) return true;  // left
    if (dir == 3 && blank % 3 != 2) return true;  // right
    return false;
}

vector<int> Problem::move(const vector<int>& state, int dir) const {
    vector<int> newState = state;
    int blank = find(state.begin(), state.end(), 0) - state.begin();
    int swapIndex = blank;

    if (dir == 0) swapIndex = blank - 3;
    else if (dir == 1) swapIndex = blank + 3;
    else if (dir == 2) swapIndex = blank - 1;
    else if (dir == 3) swapIndex = blank + 1;

    swap(newState[blank], newState[swapIndex]);
    return newState;
}