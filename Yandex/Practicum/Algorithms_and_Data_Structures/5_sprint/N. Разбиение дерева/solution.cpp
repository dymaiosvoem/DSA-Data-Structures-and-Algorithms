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
    if (root == nullptr) {
        return std::pair(nullptr, nullptr);
    }

    if (k == 0) {
        return std::pair(nullptr, root);
    } else if (k == getSize(root)) {
        return std::pair(root, nullptr);
    }

    std::pair<Node*, Node*> BST;
    int leftSize = (root->left == nullptr) ? 0 : getSize(root->left);

    if (leftSize >= k) {
        BST = split(root->left, k);

        root->left = BST.second;
        root->size = 1 + getSize(root->left) + getSize(root->right);

        return std::pair(BST.first, root);
    } else if (leftSize + 1 == k) {
        Node* right_node = root->right;
        root->right = nullptr;

        root->size = 1 + getSize(root->left) + getSize(root->right);

        BST = { root, right_node };

        return BST;
    } else if (leftSize + 1 < k) {

    }

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