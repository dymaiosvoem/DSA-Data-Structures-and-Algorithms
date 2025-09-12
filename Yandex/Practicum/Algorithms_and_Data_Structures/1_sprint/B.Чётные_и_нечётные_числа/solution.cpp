#include <iostream>
#include <cmath>

int main() {

    /*
    Time Complexity: O(1)
    Memory Complexity: O(1)
    */

    int first, second, third;
    std::cin >> first >> second >> third;

    int result = std::abs(first % 2) + std::abs(second % 2) + std::abs(third % 2);

    if (result == 0 || result == 3) {
        std::cout << "WIN" << '\n';
    } else {
        std::cout << "FAIL" << '\n';
    }
}