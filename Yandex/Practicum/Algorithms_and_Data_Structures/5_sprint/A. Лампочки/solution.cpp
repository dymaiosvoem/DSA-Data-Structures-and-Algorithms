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
#include <algorithm>
#include <cassert>

using namespace std;

int Solution(const Node* root) {
    /*
        Time Complexity: O(N), N - count vertexes
        Memory Complexity: O(H), H - height of the tree
    */
    int value = root->value;

    if (root->left != nullptr) {
        value = std::max(value, Solution(root->left));
    }

    if (root->right != nullptr) {
        value = std::max(value, Solution(root->right));
    }

    return value;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({ 1, nullptr, nullptr });
    Node node2({ -5, nullptr, nullptr });
    Node node3({ 3, &node1, &node2 });
    Node node4({ 2, &node3, nullptr });
    assert(Solution(&node4) == 3);
}

int main() {
    test();
}
#endif