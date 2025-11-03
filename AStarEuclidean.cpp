#include "AStarEuclidean.h"
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

static void printBoard(const vector<int>& state) {
    size_t n = static_cast<size_t>(sqrt(state.size()));
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0) cout << 'b' << " ";
        else cout << state[i] << " ";
        if (i % n == n - 1) cout << '\n';
    }
}

static double euclideanHeuristic(const vector<int>& state, const vector<int>& goal) {
    double h = 0;
    size_t n = static_cast<size_t>(sqrt(static_cast<double>(state.size())));
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0) continue;
        int val = state[i];
        auto it = find(goal.begin(), goal.end(), val);
        size_t idx = distance(goal.begin(), it);
        size_t x1 = i % n, y1 = i / n;
        size_t x2 = idx % n, y2 = idx / n;
        h += sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    return h;
}

struct AComparator {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
        if (a->f != b->f) return a->f > b->f;
        return a->h > b->h;
    }
};

shared_ptr<Node> aStarEuclidean(const Problem& problem) {
    auto start = make_shared<Node>(problem.initial, nullptr, 0, euclideanHeuristic(problem.initial, problem.goal));
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, AComparator> fringe;
    fringe.push(start);

    set<vector<int>> explored;
    size_t expanded = 0;
    size_t maxFrontier = 0;

    while (!fringe.empty()) {
        auto node = fringe.top(); fringe.pop();
        ++expanded;
        maxFrontier = max(maxFrontier, fringe.size());
        cout << "The best state to expand with g(n) = " << node->g << " and h(n) = " << node->h << " is...\n";
        printBoard(node->state);
        cout << "Expanding this node...\n";
        if (problem.goalTest(node->state)) {
            cout << "Goal!!!\n";
            cout << "To solve this problem the search algorithm expanded a total of " << expanded << " nodes.\n";
            cout << "The maximum number of nodes in the queue at any one time: " << maxFrontier << "\n";
            cout << "The depth of the goal node was " << node->g << ".\n";
            cout << "[A* Euclidean] nodes expanded: " << expanded << "\n";
            return node;
        }

        explored.insert(node->state);
        for (auto& child : problem.getNeighbors(node)) {
            child->h = euclideanHeuristic(child->state, problem.goal);
            child->f = child->g + child->h;
            if (explored.count(child->state)) continue;
            fringe.push(child);
        }
    }

    cout << "[A* Euclidean] nodes expanded: " << expanded << "\n";
    return nullptr;
}
