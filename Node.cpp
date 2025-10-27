#include "Node.h"
using namespace std;

Node::Node() : state{}, parent{nullptr}, g{0}, h{0}, f{0} {}

Node::Node(vector<int> state, shared_ptr<Node> parent, int g, double h)
    : state(state), parent(parent), g(g), h(h), f(g + h) {
        assert(state.size() == 9 && "State must have 9 elements for 8-puzzle");
    }

bool Node::operator<(const Node& other) const {
    return f > other.f;  
}

bool Node::operator==(const Node& other) const {
    return state == other.state;
}
