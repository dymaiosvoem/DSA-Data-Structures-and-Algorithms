#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void ComputeDpAndPrintMaxFlowers(std::vector<std::vector<size_t>>& dp_field, size_t rows, size_t columns) {
	for (size_t r = rows; r > 0; ) {
		--r;

		for (size_t c = 1; c <= columns; ++c) {
			dp_field[r][c] = dp_field[r][c] + std::max(dp_field[r + 1][c], dp_field[r][c - 1]);
		}
	}

	size_t max_flowers = dp_field[0][columns];
	std::cout << max_flowers << '\n';
}

void RestoreAndPrintPath(const std::vector<std::vector<size_t>>& dp_field, size_t rows, size_t columns) {
	std::stack<char> path;

	size_t current_r = 0, current_c = columns;

	while (current_r != rows - 1 || current_c != 1) {
		if (current_c == 1) {
			path.push('U');

			++current_r;
		} else if (current_r == rows - 1) {
			path.push('R');

			--current_c;
		} else {
			if (dp_field[current_r + 1][current_c] > dp_field[current_r][current_c - 1]) {
				path.push('U');

				++current_r;
			} else {
				path.push('R');

				--current_c;
			}
		}
	}

	while (!path.empty()) {
		std::cout << path.top();

		path.pop();
	}

	std::cout << '\n';
}

int main() {
	size_t rows, columns;
	std::cin >> rows >> columns;

	std::vector<std::vector<size_t>> dp_field(rows + 1, std::vector<size_t>(columns + 1, 0));

	for (size_t r = 0; r < rows; ++r) {

		std::string flowers_str;
		std::cin >> flowers_str;

		for (size_t c = 1; c <= columns; ++c) {
			dp_field[r][c] = (flowers_str[c - 1] == '1' ? 1 : 0);
		}
	}

	/*
		Time Complexity: O(R * C)
						R - rows, C - columns
						ComputeDpAndPrintMaxFlowers: O(R * C) 
						RestoreAndPrintPath: O(R + C)
		Memory Complexity: O(R * C)
						dp_field: O(R * C)
						path: O(R + C)
	*/
	ComputeDpAndPrintMaxFlowers(dp_field, rows, columns);
	RestoreAndPrintPath(dp_field, rows, columns);
}