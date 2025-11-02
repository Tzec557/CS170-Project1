#include "UniformCost.h"
#include "Problem.h"
#include <queue>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

static void printBoard(const vector<int>& state) {
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0) cout << 'b' << " ";
        else cout << state[i] << " ";
        if (i % 3 == 2) cout << '\n';
    }
}

using namespace std;

struct UCComparator {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
    if (a->g != b->g) return a->g > b->g; // min-heap by g
    return a->h > b->h; // tie-breaker: smaller h preferred
    }
};

shared_ptr<Node> uniformCostSearch(const Problem& problem) {
    auto start = make_shared<Node>(problem.initial);
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, UCComparator> fringe;
    fringe.push(start);

    set<vector<int>> explored;
    size_t expanded = 0;
    size_t maxFrontier = 0;

    while (!fringe.empty()) {
        auto node = fringe.top(); fringe.pop();
        ++expanded;
        maxFrontier = max(maxFrontier, fringe.size());
        // cout << "The best state to expand with g(n) = " << node->g << " and h(n) = " << node->h << " is...\n";
        // printBoard(node->state);
        // cout << "Expanding this node...\n";
        if (problem.goalTest(node->state)) {
            // cout << "Goal!!!\n";
            cout << "To solve this problem the search algorithm expanded a total of " << expanded << " nodes.\n";
            cout << "The maximum number of nodes in the queue at any one time: " << maxFrontier << "\n";
            cout << "The depth of the goal node was " << node->g << ".\n";
            cout << "[UniformCost] nodes expanded: " << expanded << "\n";
            return node;
        }
        explored.insert(node->state);
        for (auto& child : problem.getNeighbors(node)) {
            if (explored.count(child->state)) continue;
            fringe.push(child);
        }
    }
    cout << "[UniformCost] nodes expanded: " << expanded << "\n";
    return nullptr;
}
