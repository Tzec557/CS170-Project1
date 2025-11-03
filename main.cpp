#include <iostream>
#include "Node.h"
#include "Problem.h"
#include "UniformCost.h"
#include "AStarMisplaced.h"
#include "AStarEuclidean.h"
#include <chrono>
#include <algorithm> 
#include <sstream> 
using namespace std;

void printState(shared_ptr<Node> node) {
    for (int i = 0; i < 9; i++) {
        if (node->state[i] == 0) cout << 'b' << " ";
        else cout << node->state[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << "g = " << node->g << endl;
    cout << "-------------------" << endl;
}

void printSolution(shared_ptr<Node> goal) {
    if (!goal) return;
    vector<shared_ptr<Node>> path;
    for (auto n = goal; n != nullptr; n = n->parent) path.push_back(n);
    // path.puscd h_back(n);
    reverse(path.begin(), path.end());
    cout << "Solution path (" << path.size()-1 << " moves):\n";
    for (auto &n : path) {
       for (size_t i = 0; i < n->state.size(); ++i) {
           cout << n->state[i] << " ";
           if (i % 3 == 2) cout << '\n';
       }
       cout << "g=" << n->g << "\n";
       cout << "---\n";
    }
}

int main() {
    cout << "Welcome to Trikaru's 8-puzzle solver!\n";
    cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle: ";
    int choice;
    cin >> choice;

    vector<int> initial(9);
    if (choice == 1) {
        initial ={8,7,1,6,0,2,5,4,3}; //{3,1,2,4,0,6,7,5,8}; 
    } else {
        cout << "Enter your puzzle as 9 numbers (0 for blank), separated by spaces:\n";
        for (int i = 0; i < 9; ++i) {
            cin >> initial[i];
        }
    }

    vector<int> goal = {1,2,3,4,5,6,7,8,0}; 
    Problem problem(initial, goal);

    cout << "Enter your choice of algorithm:\n";
    cout << "1: Uniform Cost Search\n";
    cout << "2: A* Misplaced Tile\n";
    cout << "3: A* Euclidean Distance\n";
    int algChoice;
    cin >> algChoice;

    shared_ptr<Node> solution;
    auto startTime = chrono::high_resolution_clock::now();
    switch(algChoice) {
        case 1: solution = uniformCostSearch(problem); break;
        case 2: solution = aStarMisplaced(problem); break;
        case 3: solution = aStarEuclidean(problem); break;
        default: cout << "Invalid choice.\n"; return 1;
    }
    auto endTime = chrono::high_resolution_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    if (solution) {
        cout << "Found solution with g=" << solution->g << " in " << us << " us\n";
        printSolution(solution);
    } else {
        cout << "No solution found (" << us << " us)\n";
    }

return 0;

}
    //test Problem class
    // vector<int> initial = {3, 1, 2, 4, 0, 6, 7, 5, 8};
    // vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    // auto countInversions = [](const vector<int>& v) {
    //     int inv = 0;
    //     for (size_t i = 0; i < v.size(); ++i) {
    //         if (v[i] == 0) continue;
    //         for (size_t j = i + 1; j < v.size(); ++j) {
    //             if (v[j] == 0) continue;
    //             if (v[i] > v[j]) ++inv;
    //         }
    //     }
    //     return inv;
    // };

    // auto isSolvable3x3 = [&](const vector<int>& start, const vector<int>& goal) {
    //     return (countInversions(start) % 2) == (countInversions(goal) % 2);
    // };

    // if (!isSolvable3x3(initial, goal)) {
    //     cout << "Initial state is unsolvable (inversions parity mismatch). Exiting.\n";
    //     return 0;
    // }

    // Problem problem(initial, goal);
    // auto startNode = make_shared<Node>(initial);
    // cout << "Start node:" << endl;
    // printState(startNode);

    // cout << "Is start goal? " << (problem.goalTest(startNode->state) ? "Yes" : "No") << endl;

    // Uniform Cost Search
//     {
//         using clock = chrono::high_resolution_clock;
//         auto t0 = clock::now();
//         auto sol = uniformCostSearch(problem);
//         auto t1 = clock::now();
//         auto us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
//         cout << "Uniform Cost: ";
//         if (sol) {
//             cout << "Found solution with g=" << sol->g << " in " << us << " us\n";
//             printSolution(sol);
//         } else cout << "No solution (" << us << " us)\n";
//     }

//     // A* (misplaced tile)
//     {
//         using clock = chrono::high_resolution_clock;
//         auto t0 = clock::now();
//         auto sol = aStarMisplaced(problem);
//         auto t1 = clock::now();
//         auto us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
//         cout << "A* (misplaced): ";
//         if (sol) {
//             cout << "Found solution with g=" << sol->g << " in " << us << " us\n";
//             printSolution(sol);
//         } else cout << "No solution (" << us << " us)\n";
//     }

//     // A* (euclidean)
//     {
//         using clock = chrono::high_resolution_clock;
//         auto t0 = clock::now();
//         auto sol = aStarEuclidean(problem);
//         auto t1 = clock::now();
//         auto us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
//         cout << "A* (Euclidean): ";
//         if (sol) {
//             cout << "Found solution with g=" << sol->g << " in " << us << " us\n";
//             printSolution(sol);
//         } else cout << "No solution (" << us << " us)\n";
//     }
//     return 0;
// }

/*
referenced: 

https://gist.github.com/sameer-j/76c38850f876661daf5d
https://github.com/sevdeawesome/A-Star-Search
https://sandipanweb.wordpress.com/2017/03/16/using-uninformed-informed-search-algorithms-to-solve-8-puzzle-n-puzzle/

*/ 
