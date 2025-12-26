#include <algorithm>
#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

int MaxChildIndex(const std::vector<int>& heap, int idx_left_child, int idx_right_child) {
    if (heap[idx_left_child] > heap[idx_right_child]) {
        return idx_left_child;
    } else {
        return idx_right_child;
    }
}

int siftDown(std::vector<int>& heap, int idx) {
    /*
        Time Complexity: O(log N)
        Memory Complexity: O(1)
    */
    while (true) {
        int idx_left_child = 2 * idx;

        if (idx_left_child >= heap.size()) {
            return idx;
        }

        int idx_right_child = (2 * idx) + 1;

        if (idx_right_child >= heap.size()) {
            if (heap[idx] < heap[idx_left_child]) {
                std::swap(heap[idx], heap[idx_left_child]);
                idx = idx_left_child;
            } else {
                return idx;
            }
        } else {
            int best_child = MaxChildIndex(heap, idx_left_child, idx_right_child);

            if (heap[idx] < heap[best_child]) {
                std::swap(heap[idx], heap[best_child]);
                idx = best_child;
            } else {
                return idx;
            }
        }
    }
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = { -1, 12, 1, 8, 3, 4, 7 };
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif