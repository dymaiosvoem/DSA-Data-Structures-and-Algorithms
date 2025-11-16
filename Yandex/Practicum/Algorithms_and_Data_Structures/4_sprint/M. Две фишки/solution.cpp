#include <iostream>
#include <vector>

void NaiveSolution(const std::vector<int>& points_on_chips, int k) {
	/*
		Time Complexity: max comparisons N(N - 1) / 2 = (N^2 - N) / 2 = N^2
		Memory Complexity: O(1)
	*/
	for (size_t i = 0; i < points_on_chips.size(); ++i) {
		for (size_t j = i + 1; j < points_on_chips.size(); ++j) {
			if (points_on_chips[i] + points_on_chips[j] == k) {
				std::cout << points_on_chips[i] << ' ' << points_on_chips[j] << '\n';
				return;
			}
		}
	}

	std::cout << "None" << '\n';
}

void SortSolution(const std::vector<int>& points_on_chips, int k) {
	/*
		Time Complexity:
		Memory Complexity:
	*/
}

void UnorderedSetSolution(const std::vector<int>& points_on_chips, int k) {
	/*
		Time Complexity:
		Memory Complexity:
	*/
}

int main() {
	size_t count_chips;
	std::cin >> count_chips;

	std::vector<int> points_on_chips(count_chips);

	for (size_t i = 0; i < count_chips; ++i) {
		std::cin >> points_on_chips[i];
	}

	int k;
	std::cin >> k;

	NaiveSolution(points_on_chips, k);
	SortSolution(points_on_chips, k);
	UnorderedSetSolution(points_on_chips, k);
}