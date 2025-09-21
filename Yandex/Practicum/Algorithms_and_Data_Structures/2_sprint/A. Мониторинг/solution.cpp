#include <iostream>
#include <vector>

void Solution(std::vector<int>& matrix, size_t row, size_t column) {
	/*
		Time Complexity: O(R * C)
		Memory Comlexity: O(N) N - size matrix
	*/
	size_t start = 0;

	for (size_t i = 0; i < row; ++i) {
		while (start < column) {
			int num;
			std::cin >> num;

			matrix[start * row + i] = num;
			++start;
		}

		start = 0;
	}

	for (size_t i = 0; i < column; ++i) {
		for (size_t j = 0; j < row; ++j) {
			if (j) {
				std::cout << ' ';
			}
			std::cout << matrix[i * row + j];
		}
		std::cout << '\n';
	}
}

int main() {
	size_t row, column;
	std::cin >> row >> column;

	size_t mtrx_size = column * row;
	std::vector<int> matrix(mtrx_size, 0);

	Solution(matrix, row, column);
}