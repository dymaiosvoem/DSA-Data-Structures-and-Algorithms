#ifndef REMOTE_JUDGE
struct Node {
    int value;
    const Node* left = nullptr;
    const Node* right = nullptr;
    Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cassert>
#include <climits>
#include <stack>

using namespace std;

struct NodeData {
    NodeData(const Node* node, int min_value, int max_value)
        : node_(node), min_value_(min_value), max_value_(max_value) {
    }

    const Node* node_;
    int min_value_;
    int max_value_;
};

bool Solution(const Node* root) {
    /*
        Time Complexity: O(N), N - count of vertexes
        Memory Complexity: O(H), H - height of tree
    */
    if (root == nullptr) {
        return true;
    }

    std::stack<NodeData> stack;
    stack.push(NodeData(root, INT_MIN, INT_MAX));

    while (!stack.empty()) {
        NodeData current = stack.top();
        stack.pop();

        const Node* node = current.node_;
        int value = node->value;

        if (current.min_value_ >= value || value >= current.max_value_) {
            return false;
        }

        if (current.node_->left != nullptr) {
            stack.push(NodeData(current.node_->left, current.min_value_, value));
        }

        if (current.node_->right != nullptr) {
            stack.push(NodeData(current.node_->right, value, current.max_value_));
        }
    }

    return true;
}


#ifndef REMOTE_JUDGE
void test() {
    {
        Node node1({ 1, nullptr, nullptr });
        Node node2({ 4, nullptr, nullptr });
        Node node3({ 3, &node1, &node2 });
        Node node4({ 8, nullptr, nullptr });
        Node node5({ 5, &node3, &node4 });
        assert(Solution(&node5));
    }
    {
        Node node1({ 1, nullptr, nullptr });
        Node node2({ 5, nullptr, nullptr });
        Node node3({ 3, &node1, &node2 });
        Node node4({ 8, nullptr, nullptr });
        Node node5({ 5, &node3, &node4 });
        assert(!Solution(&node5));
    }
}


int main() {
    test();
}
#endif