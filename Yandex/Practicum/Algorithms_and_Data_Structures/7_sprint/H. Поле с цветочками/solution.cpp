#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

size_t ComputeMaxFlowers(std::vector<std::vector<size_t>>& dp_field, size_t rows, size_t columns) {
	/*
		Time Complexity: O(R * C) R - rows, C - columns
		Memory Complexity: O(R * C)
	*/
	for (size_t r = rows; r > 0; ) {
		--r;

		for (size_t c = 1; c <= columns; ++c) {
			dp_field[r][c] = dp_field[r][c] + std::max(dp_field[r + 1][c], dp_field[r][c - 1]);
		}
	}

	return dp_field[0][columns];
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

	auto max_flowers = ComputeMaxFlowers(dp_field, rows, columns);
	std::cout << max_flowers << '\n';
}