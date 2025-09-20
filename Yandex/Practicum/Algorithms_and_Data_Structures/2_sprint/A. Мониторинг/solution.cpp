#include <iostream>
#include <vector>

void Solution(std::vector<std::vector<int>>& mtrx) {

}

int main() {
	size_t row, column;
	std::cin >> row >> column;

	size_t mtrx_size = column * row;

	std::vector<int> matrix(mtrx_size, 0);

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

	bool space = true;

	for (size_t i = 0; i < mtrx_size; ++i) {
		if (space) {
			std::cout << matrix[i];
			space = false;
			continue;
		} else if (row == 1) {
			std::cout << '\n';
			std::cout << matrix[i];
			continue;
		}

		std::cout << ' ' << matrix[i];

		if (i != 0 && (i + 1) % row == 0) {
			std::cout << '\n';
			space = true;
		}
	}
}