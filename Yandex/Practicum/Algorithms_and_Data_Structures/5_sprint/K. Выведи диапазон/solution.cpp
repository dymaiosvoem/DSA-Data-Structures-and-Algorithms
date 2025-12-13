#ifndef REMOTE_JUDGE
struct Node {
    int value;
    const Node* left = nullptr;
    const Node* right = nullptr;
    Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <iostream>

using namespace std;

void DepthFirstSearch(const Node* root, int l, int r) {
    if (root == nullptr) {
        return;
    }

    if (l <= root->value && root->left != nullptr) {
        DepthFirstSearch(root->left, l, r);
    }

    if (l <= root->value && root->value <= r) {
        std::cout << root->value << '\n';
    }

    if (root->value <= r && root->right != nullptr) {
        DepthFirstSearch(root->right, l, r);
    }
}

void print_range(Node* root, int l, int r) {
    /*
        Time Complexity: O(H + k), H - height of the tree, k - count elements [l, r]
        Memory Complexity: O(H)
    */
    DepthFirstSearch(root, l, r);
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({ nullptr, nullptr, 2 });
    Node node2({ nullptr, &node1, 1 });
    Node node3({ nullptr, nullptr, 8 });
    Node node4({ nullptr, &node3, 8 });
    Node node5({ &node4, nullptr, 9 });
    Node node6({ &node5, nullptr, 10 });
    Node node7({ &node2, &node6, 5 });
    print_range(&node7, 2, 8);
    // expected output: 2 5 8 8
}

int main() {
    test();
}
#endif