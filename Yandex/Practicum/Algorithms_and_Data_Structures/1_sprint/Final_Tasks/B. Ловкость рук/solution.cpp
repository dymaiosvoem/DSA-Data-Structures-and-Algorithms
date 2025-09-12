#include <array>
#include <iostream>

void Solution(const std::array<unsigned int, 10>& num, unsigned int clicks) {
    /*
        Time Comlexity: O(N * L) N - row count, L - row length
        Memory Complexity: O(1)
    */
    unsigned int result = 0;

    for (size_t j = 1; j < num.size(); ++j) {
        if (num[j] <= clicks && num[j] > 0) {
            ++result;
        }
    }

    std::cout << result << '\n';
}

int main() {
    unsigned int k;
    std::cin >> k;

    unsigned int max_clicks = k * 2;
    std::array<unsigned int, 10> numbers{};

    size_t start = 0, end = 4;

    while (start < end) {
        std::string line;
        std::cin >> line;

        for (size_t i = 0; i < 4; ++i) {
            if (line[i] == '.') {
                ++numbers[0];
                continue;
            }

            ++numbers[line[i] - '0'];
        }

        ++start;
    }

    Solution(numbers, max_clicks);
}