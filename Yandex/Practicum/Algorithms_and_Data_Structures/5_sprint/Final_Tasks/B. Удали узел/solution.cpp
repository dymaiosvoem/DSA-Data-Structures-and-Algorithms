#ifndef REMOTE_JUDGE
struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>

int ExtractSuccessor(Node* root) {
    Node* parent = root;
    Node* successor = parent->right;

    if (successor->left == nullptr) {
        parent->right = successor->right;
    } else {
        while (successor->left != nullptr) {
            parent = successor;

            successor = successor->left;
        }

        parent->left = successor->right;
    }

    return successor->value;
}

Node* remove(Node* root, int key) {
    /*
        Time Complexity: O(H), H - height of the tree
        Memory Complexity: O(H)
    */
    if (root == nullptr) {
        return nullptr;
    }

    if (key == root->value) {
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr;
        } else if (root->left != nullptr && root->right != nullptr) {
            int successor_value = ExtractSuccessor(root);

            root->value = successor_value;
            return root;
        } else {
            return (root->left == nullptr) ? root->right : root->left;
        }
    }

    if (key < root->value) {
        root->left = remove(root->left, key);
    } else if (key > root->value) {
        root->right = remove(root->right, key);
    }

    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({ nullptr, nullptr, 2 });
    Node node2({ &node1, nullptr, 3 });
    Node node3({ nullptr, &node2, 1 });
    Node node4({ nullptr, nullptr, 6 });
    Node node5({ &node4, nullptr, 8 });
    Node node6({ &node5, nullptr, 10 });
    Node node7({ &node3, &node6, 5 });
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);

    Node node11({ nullptr, nullptr, 2 });
    Node node12({ &node11, nullptr, 3 });
    Node node13({ nullptr, &node12, 1 });
    Node node14({ nullptr, nullptr, 6 });
    Node node15({ &node14, nullptr, 8 });
    Node node19({ nullptr, nullptr, 11 });
    Node node18({ &node19, nullptr, 12 });
    Node node16({ &node15, &node18, 10 });
    Node node17({ &node13, &node16, 5 });
    Node* newHead1 = remove(&node17, 10);
    assert(newHead1 == &node17);
    assert(newHead1->value == 5);
    assert(newHead1->right == &node16);
    assert(newHead1->right->value == 11);
    assert(newHead1->right->left == &node15);
    assert(newHead1->right->left->value == 8);
    assert(newHead1->right->left->left == &node14);
    assert(newHead1->right->left->left->value == 6);

    Node node111({ nullptr, nullptr, 2 });
    Node node222({ &node111, nullptr, 3 });
    Node node333({ nullptr, &node222, 1 });
    Node node444({ nullptr, nullptr, 6 });
    Node node555({ &node444, nullptr, 8 });
    Node node666({ &node555, nullptr, 10 });
    Node node777({ &node333, &node666, 5 });
    Node* newHead11 = remove(&node777, 1);
    assert(newHead11->value == 5);
    assert(newHead11->left == &node222);
    assert(newHead11->left->value == 3);
}

int main() {
    test();
}
#endif