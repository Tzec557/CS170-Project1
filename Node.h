#ifndef NODE_H
#define NODE_H

#include <vector>
#include<memory>
#include <cassert>

using namespace std;

class Node{
    public:
        vector<int> state;
        shared_ptr<Node> parent;
        int g;
        double h;
        double f;

        Node();
        Node(vector<int> state, shared_ptr<Node> parent = nullptr, int g = 0, double h = 0);
        
        bool operator<(const Node& other) const;
        bool operator==(const Node& other) const;
};
#endif