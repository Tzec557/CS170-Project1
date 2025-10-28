#include <iostream>
#include "Node.h"
#include "Problem.h"
using namespace std;

void printState(shared_ptr<Node> node) {
    for (int i = 0; i < 9; i++) {
        cout << node->state[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << "g = " << node->g << endl;
    cout << "-------------------" << endl;
}

int main() {
    //test Problem class
    vector<int> initial = {1, 3, 2, 4, 0, 6,7, 5, 8};
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Problem problem(initial, goal);
    auto startNode = make_shared<Node>(initial);

    cout << "Start node:" << endl;
    printState(startNode);
    
    //test goalTest
    cout << "Is start goal? " << (problem.goalTest(startNode->state) ? "Yes" : "No") << endl;
    
    //test getNeighbors
    vector<shared_ptr<Node>> neighbors = problem.getNeighbors(startNode);

    cout << "Neighbors of start node:" << endl;
    for (auto& child : neighbors) {
        printState(child);
    }

    //test node class
    vector<int> board = {1, 3, 0, 4, 2, 6, 7, 5, 8};
    auto node = make_shared<Node>(board, nullptr, 0, 5.0);
    cout << "Board state:\n";
    for (int i = 0; i < 9; i++) {
        cout << node->state[i] << " ";
        if (i % 3 == 2) cout << "\n";
    }
    cout << "g = " << node->g << "\n";
    cout << "h = " << node->h << "\n";
    cout << "f = " << node->f << "\n";

    auto parentBoard = vector<int>{1, 0, 3, 4, 2, 6, 7, 5, 8};
    auto parentNode = make_shared<Node>(parentBoard, nullptr, 0, 3.0);
    node->parent = parentNode;

    cout << "Parent board:\n";
    for (int i = 0; i < 9; i++) cout << node->parent->state[i] << " ";
    cout << "\n";
    return 0;
}