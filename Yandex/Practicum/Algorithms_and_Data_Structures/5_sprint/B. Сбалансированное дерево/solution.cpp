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
#include <cstdlib>
#include <optional>

using namespace std;

std::optional<int> IsAVL(const Node* root) {
    if (root == nullptr) {
        return 0;
    }

    std::optional<int> Hl, Hr;

    Hl = (root->left == nullptr ? 0 : IsAVL(root->left));

    Hr = (root->right == nullptr ? 0 : IsAVL(root->right));

    if (Hl.has_value() && Hr.has_value()) {
        if (std::abs(*Hl - *Hr) <= 1) {
            return 1 + std::max(*Hl, *Hr);
        } else {
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }
}

bool Solution(const Node* root) {
    /*
        Time Complexity: O(N), N - count vertexes
        Memory Complexity: O(H), H - height of the tree
    */
    auto result = IsAVL(root);

    return result.has_value();
}


#ifndef REMOTE_JUDGE
void test() {
    Node node1({ 1, nullptr, nullptr });
    Node node2({ -5, nullptr, nullptr });
    Node node3({ 3, &node1, &node2 });
    Node node4({ 10, nullptr, nullptr });
    Node node5({ 2, &node3, &node4 });
    assert(Solution(&node5));
}

int main() {
    test();
}
#endif