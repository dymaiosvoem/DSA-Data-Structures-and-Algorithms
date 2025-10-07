#include <iostream>
#include <vector>

void PrintContainer(const std::vector<int>& container) {
    for (size_t start = 0; start < container.size(); ++start) {
        if (start) {
            std::cout << ' ';
        }
        std::cout << container[start];
    }
    std::cout << '\n';
}

void Solution(std::vector<int>& arr, size_t size) {
    /*
        Time Complexity: O(N^2)
        Memory Complexity: O(1)
    */
    size_t count_passes = 0;

    while (size != 1) {
        bool swapped = false;

        for (size_t start = 0; start < size - 1; ++start) {
            if (arr[start] > arr[start + 1]) {
                int current_value = arr[start];
                arr[start] = arr[start + 1];
                arr[start + 1] = current_value;

                swapped = true;
            }
        }

        if (!swapped) {
            if (count_passes == 0) {
                PrintContainer(arr);
            }
            break;
        } else {
            PrintContainer(arr);
        }

        --size;
        ++count_passes;
    }
}

int main() {
    size_t size;
    std::cin >> size;

    std::vector<int> arr(size, 0);

    for (size_t start = 0; start < arr.size(); ++start) {
        std::cin >> arr[start];
    }

    Solution(arr, size);
}