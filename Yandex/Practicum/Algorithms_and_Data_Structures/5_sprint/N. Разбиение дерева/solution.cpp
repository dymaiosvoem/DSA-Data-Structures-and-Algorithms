#ifndef REMOTE_JUDGE
struct Node {
    Node* left;
    Node* right;
    int value;
    int size;
};
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>
#include <utility>

int getSize(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}

std::pair<Node*, Node*> split(Node* root, int k) {
    /*
        Time Complexity: O(H), H - height of the tree
        Memory Complexity: O(H), recursion stack
    */
    if (root == nullptr) {
        return { nullptr, nullptr };
    } else if (k == 0) {
        return { nullptr, root };
    } else if (k == getSize(root)) {
        return { root, nullptr };
    }

    int leftSize = (root->left == nullptr) ? 0 : getSize(root->left);

    if (k <= leftSize) {
        auto [A_left, B_right] = split(root->left, k);

        root->left = B_right;
        root->size = 1 + getSize(root->left) + getSize(root->right);

        return { A_left, root };

    } else if (k == leftSize + 1) {
        Node* right_node = root->right;

        root->right = nullptr;
        root->size = 1 + getSize(root->left) + getSize(root->right);

        return { root, right_node };
    } else if (k > leftSize + 1) {
        auto [A_right, B] = split(root->right, k - (leftSize + 1));

        root->right = A_right;
        root->size = 1 + getSize(root->left) + getSize(root->right);

        return { root, B };
    }

    return { nullptr, nullptr };
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({ nullptr, nullptr, 3, 1 });
    Node node2({ nullptr, &node1, 2, 2 });
    Node node3({ nullptr, nullptr, 8, 1 });
    Node node4({ nullptr, nullptr, 11, 1 });
    Node node5({ &node3, &node4, 10, 3 });
    Node node6({ &node2, &node5, 5, 6 });
    std::pair<Node*, Node*> res = split(&node6, 4);
    assert(res.first->size == 4);
    assert(res.second->size == 2);
}


int main() {
    test();
}
#endif