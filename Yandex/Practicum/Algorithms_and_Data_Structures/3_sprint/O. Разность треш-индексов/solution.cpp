#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

using Tuple = std::tuple<std::vector<size_t>, std::vector<size_t>, std::vector<size_t>>;

Tuple partition(const std::vector<size_t>& square_of_islands, size_t pivot) {
	std::vector<size_t> left, mid, right;

	for (const auto& s : square_of_islands) {
		if (s < pivot) {
			left.push_back(s);
		} else if (s == pivot) {
			mid.push_back(s);
		} else {
			right.push_back(s);
		}
	}

	return { left, mid, right };
}

std::vector<size_t> QuickSort(const std::vector<size_t>& square_of_islands) {
	if (square_of_islands.size() <= 1) {
		return square_of_islands;
	}

	size_t pivot = square_of_islands[rand() % square_of_islands.size()];
	auto [left, mid, right] = partition(square_of_islands, pivot);

	left = QuickSort(left);
	right = QuickSort(right);

	std::vector<size_t> result(left.begin(), left.end());
	result.insert(result.end(), mid.begin(), mid.end());
	result.insert(result.end(), right.begin(), right.end());

	return result;
}

void Solution(const std::vector<size_t>& square_of_islands, size_t pos_difference_result) {
	std::vector<size_t> sorted_squares = QuickSort(square_of_islands);

	std::vector<size_t> differences_of_squares;
	differences_of_squares.reserve(square_of_islands.size());

	size_t i = 0, j = 1;

	while (i < sorted_squares.size()) {
		if (j == sorted_squares.size()) {
			++i;

			if (i == sorted_squares.size() - 1) {
				break;
			}

			j = i + 1;
		}

		size_t difference = 0;

		if (sorted_squares[i] >= sorted_squares[j]) {
			difference = sorted_squares[i] - sorted_squares[j];
		} else {
			difference = sorted_squares[j] - sorted_squares[i];
		}

		differences_of_squares.push_back(difference);
		++j;
	}

	std::vector<size_t> sorted_differences = QuickSort(differences_of_squares);

	std::cout << sorted_differences[pos_difference_result - 1];
}

int main() {
	size_t count_islands;
	std::cin >> count_islands;

	std::vector<size_t> square_of_islands(count_islands);
	for (size_t i = 0; i < count_islands; ++i) {
		std::cin >> square_of_islands[i];
	}

	size_t pos_difference_result;
	std::cin >> pos_difference_result;

	Solution(square_of_islands, pos_difference_result);
}