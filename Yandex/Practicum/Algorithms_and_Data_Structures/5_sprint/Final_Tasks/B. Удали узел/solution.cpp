/*
    -- ПРИНЦИП РАБОТЫ --
    На вход подается корень дерева. Начинаю сравнивать key и root->value.
        -если key < root->value, то спускаюсь в левое поддерево;
        -если key > root->value, то спускаюсь в правое поддерево;

    Когда встречаю key == root->value, существует 3 вариант удаления вершины из дерева
        1) когда у удаляемой вершины 0 детей: root->left == nullptr && root->right == nullptr;
            -возвращаю на верх nullptr;
        2) когда у удаляемой вершины 2 ребенка: root->left != nullptr && root->right != nullptr;
            -для себя решил делать замену на Successor(минимальное значение правого поддерева от удаляемой вершины);
            -в хелпере прохожу итеративно, задав Node* parent = root; Node* successor = parent->right:
                1) if successor->left == nullptr, делаю parent->right = successor->right;
                2) if successor->left != nullptr, иду в самую левую вершину while (successor->left != nullptr), делаю 
                parent->left = successor->right;
                3) возвращаю значение return successor->value;
                4) перезаписываю значение у удаляемой вершины на Successor (root->value = successor_value), возвращаю root.
        3) когда у удаляемой вершины 1 ребенок:
            -поднимаю правое/левое поддерево выше: return (root->left == nullptr) ? root->right : root->left;

    Если дошел до nullptr, то вершины с таким key нет и дерево не меняю.

    -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
    Для каждой вершины все значения в левом поддереве меньше значения вершины, в правом - больше.

    1) База: если root == nullptr, функция возвращает nullptr, дерево пустое.
        Инвариант сохраняется, элемент не найден, ничего не поменял.

    2) Поиск:
       -если key < root->value, удаление выполняется только в левом поддереве: root->left = remove(root->left, key).
       -если key > root->value, удаление выполняется только в правом поддереве: root->right = remove(root->right, key).

    3) Случай key == root->value (вершина найдена). Возможны 3 варианта:
       -0 детей: возврат nullptr, удаляю лист, BST не нарушается.
       -1 ребенок: возвращается единственный ребенок, удаляется нужная вершина, поддерево поднимается, BST не нарушается. 
       -2 ребенка: выбирается successor - минимальный элемент правого поддерева.
          ExtractSuccessor вырезает successor из правого поддерева, заменяя его на successor->right 
          (у successor нет левого ребенка, правый может быть).
          Затем значение successor копируется в текущую вершину.

        Successor больше всех элементов левого поддерева и минимальный элемент в правом поддереве, поэтому после замены BST сохраняется.

    -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    Пусть N - количество узлов. Поиск удаляемого узла идет вниз по одному ребру за шаг, в худшем случае дерево будет как связный
    список: O(N).

    Если у найденного узла 2 ребенка, то в ExtractSuccessor спускаюсь по правому поддереву до минимального элемента,
    в худшем случае это тоже может занять O(N).

    Итог: O(N).

    -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    Дополнительные контейнеры для хранения вершин не использую: O(1), кроме стека вызовов (рекурсия).

    В худшем случае глубина стека = количеству узлов: O(N), при сбалансированном дереве O(log N).

    ExtractSuccessor итеративный: O(1).

    Итог: O(N).
*/

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