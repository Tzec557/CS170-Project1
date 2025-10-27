#include <iostream>
#include "Node.h"
using namespace std;

int main() {
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