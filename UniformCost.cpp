#include "UniformCost.h"
#include "Problem.h"
#include <queue>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

static void printBoard(const vector<int>& state) {
    // Helper: print a board state using 'b' for the blank (0)
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0) cout << 'b' << " ";
        else cout << state[i] << " ";
        if (i % 3 == 2) cout << '\n';
    }
}

using namespace std;

struct UCComparator {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
    // Priority queue comparator
    // Prefer lower g (path cost). If g ties, prefer lower h as a tie-breaker.
    if (a->g != b->g) return a->g > b->g; // min-heap by g
    return a->h > b->h; // tie-breaker: smaller h preferred
    }
};

shared_ptr<Node> uniformCostSearch(const Problem& problem) {
    auto start = make_shared<Node>(problem.initial);
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, UCComparator> fringe;
    fringe.push(start);

    // Explored (closed) set: stores states that have been expanded already (graph-search behavior)
    set<vector<int>> explored;
    // Metrics for reporting
    size_t expanded = 0;        // number of nodes expanded
    size_t maxFrontier = 0;     // maximum size of the frontier during search

    while (!fringe.empty()) {
        auto node = fringe.top(); fringe.pop();
        // 1) Pop best node (lowest g)
        ++expanded; // count this expansion
        // track maximum frontier size (for memory analysis)
        maxFrontier = max(maxFrontier, fringe.size());

        // Trace output (useful for verbal walkthroughs): show selected node and that it is being expanded
        cout << "The best state to expand with g(n) = " << node->g << " and h(n) = " << node->h << " is...\n";
        printBoard(node->state);
        cout << "Expanding this node...\n";

        // 2) If this popped node is the goal, we are done (UCS guarantees optimal g)
        if (problem.goalTest(node->state)) {
            cout << "Goal!!!\n";
            cout << "To solve this problem the search algorithm expanded a total of " << expanded << " nodes.\n";
            cout << "The maximum number of nodes in the queue at any one time: " << maxFrontier << "\n";
            cout << "The depth of the goal node was " << node->g << ".\n";
            cout << "[UniformCost] nodes expanded: " << expanded << "\n";
            return node;
        }

        // 3) Mark this state as explored (so we don't re-expand it)
        explored.insert(node->state);

        // 4) Generate neighbors (children) and add to frontier if not yet explored
        for (auto& child : problem.getNeighbors(node)) {
            // If child state already expanded, skip (graph-search)
            if (explored.count(child->state)) continue;
            // Otherwise push child onto the priority queue (may create duplicates in frontier)
            fringe.push(child);
        }
    }
    cout << "[UniformCost] nodes expanded: " << expanded << "\n";
    return nullptr;
}
