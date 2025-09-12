#include <algorithm>
#include <iostream>
#include <vector>

void Solution(size_t row_c, size_t col_c, std::vector<std::vector<int>>& m, size_t r, size_t c) {
    /*
    Time Complexity: O(1)
    Memory Complexity: O(1)
    */

    std::vector<int> numbers;
    numbers.reserve(4);

    if (r < row_c && c < col_c) {

        // up
        if (r + 1 < row_c) {
            numbers.push_back(m[r + 1][c]);
        }

        // down
        if (r > 0) {
            numbers.push_back(m[r - 1][c]);
        }

        // left
        if (c > 0) {
            numbers.push_back(m[r][c - 1]);
        }

        // right
        if (c + 1 < col_c) {
            numbers.push_back(m[r][c + 1]);
        }
    }

    std::sort(numbers.begin(), numbers.end());
    bool space = true;

    for (auto& number : numbers) {
        if (space) {
            std::cout << number;
            space = false;

            continue;
        }
        std::cout << ' ' << number;
    }
}

int main() {
    size_t row_count, column_count;
    std::cin >> row_count >> column_count;

    std::vector<std::vector<int>> matrix(row_count, std::vector<int>(column_count));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cin >> matrix[i][j];
        }
    }

    size_t pos_row, pos_col;
    std::cin >> pos_row >> pos_col;

    Solution(row_count, column_count, matrix, pos_row, pos_col);
}