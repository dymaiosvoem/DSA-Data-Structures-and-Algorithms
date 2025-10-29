#include <vector>
#include <cassert>

int broken_search(const std::vector<int>& vec, int k) {
    /*
        Time Complexity: O(log n)
        Memory Complexity: O(1)
    */
    int left = 0, right = vec.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == k) {
            return mid;
        }

        if (vec[left] <= vec[mid]) {
            if (vec[left] <= k && k < vec[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        } else {
            if (vec[mid] < k && k <= vec[right - 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
    }

    return (left < vec.size() && vec[left] == k ? left : -1);
}

void test() {
    std::vector<int> bad = { 3, 4, 5, 6, 7, 0, 1, 2 };
    assert(7 == broken_search(bad, 2));

    std::vector<int> arr = { 19, 21, 100, 101, 1, 3, 4, 5, 7, 12 };
    assert(7 == broken_search(arr, 5));

    std::vector<int> arr_2 = { 5, 1 };
    assert(1 == broken_search(arr_2, 1));

    std::vector<int> arr_3 = { 1, 3, 4, 5, 7, 12, 19, 21, 100, 101 };
    assert(3 == broken_search(arr_3, 5));

    std::vector<int> arr_4 = { 19, 21, 100, 101, 1, 4, 5, 7, 12 };
    assert(6 == broken_search(arr_4, 5));

    std::vector<int> arr_5 = { 1 };
    assert(0 == broken_search(arr_5, 1));

    std::vector<int> arr_6 = { 4, 5, 6, 7, 0, 1, 2, 3 };
    assert(2 == broken_search(arr_6, 6));
}

int main() {
    test();
}