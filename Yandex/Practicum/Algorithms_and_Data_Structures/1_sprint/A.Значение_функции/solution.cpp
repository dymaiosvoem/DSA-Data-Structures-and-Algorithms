#include <iostream>

int main() {
    /* Time Complexity: O(1)
       Memory Complexity: O(1) */

    int a, x, b, c;
    std::cin >> a >> x >> b >> c;

    int y = (a * x * x) + (b * x) + c;

    std::cout << y << '\n';
}