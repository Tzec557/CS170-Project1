#include "AStarMisplaced.h"
#include <queue>
#include <set>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <iostream>

static void printBoard(const vector<int>& state) {
    // Helper: print board using 'b' for blank
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0) cout << 'b' << " ";
        else cout << state[i] << " ";
        if (i % 3 == 2) cout << '\n';
    }
}

using namespace std;

static double misplacedHeuristic(const vector<int>& state, const vector<int>& goal) {
    int count = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0 && state[i] != goal[i]) ++count;
    }
    return static_cast<double>(count);
}

struct AComparator {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
    // Comparator orders by f (g+h); tie-break on smaller h for reproducibility
    if (a->f != b->f) return a->f > b->f;
    return a->h > b->h; // tie-break: smaller h preferred
    }
};

shared_ptr<Node> aStarMisplaced(const Problem& problem) {
    auto start = make_shared<Node>(problem.initial, nullptr, 0, misplacedHeuristic(problem.initial, problem.goal));
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, AComparator> fringe;
    fringe.push(start);
    // Explored set (closed): avoid re-expanding states we've already expanded
    set<vector<int>> explored;
    // Metrics for reporting
    size_t expanded = 0;
    size_t maxFrontier = 0;

    while (!fringe.empty()) {
        // 1) Pop best node according to f = g + h
        auto node = fringe.top(); fringe.pop();
        ++expanded;
        maxFrontier = max(maxFrontier, fringe.size());

        // Trace for explanation: which node is selected
        cout << "The best state to expand with g(n) = " << node->g << " and h(n) = " << node->h << " is...\n";
        printBoard(node->state);
        cout << "Expanding this node...\n";

        // 2) Goal test
        if (problem.goalTest(node->state)) {
            cout << "Goal!!!\n";
            cout << "To solve this problem the search algorithm expanded a total of " << expanded << " nodes.\n";
            cout << "The maximum number of nodes in the queue at any one time: " << maxFrontier << "\n";
            cout << "The depth of the goal node was " << node->g << ".\n";
            cout << "[A* misplaced] nodes expanded: " << expanded << "\n";
            return node;
        }

        // 3) Mark as explored to enforce graph-search behavior
        explored.insert(node->state);

        // 4) Generate and push children, computing their h and f values
        for (auto& child : problem.getNeighbors(node)) {
            child->h = misplacedHeuristic(child->state, problem.goal);
            child->f = child->g + child->h;
            if (explored.count(child->state)) continue; // skip already-expanded states
            fringe.push(child); // may push duplicates if child discovered via different paths
        }
    }
    cout << "[A* misplaced] nodes expanded: " << expanded << "\n";
    return nullptr;
}
