#include <algorithm>
#include <iostream>
#include <vector>

int Compute2DpMaxGoldMass(const std::vector<int>& weight_bars, int backpack_capacity) {
	/*
		Time Complexity: O(N * M) N - number of bars, M - backpack_capacity
		Memory Complexity: O(N * M)
	*/
	int weight_size = static_cast<int>(weight_bars.size());

	std::vector<std::vector<int>> dp_max_mass(weight_size, std::vector<int>(backpack_capacity + 1, 0));

	for (int i = 1; i < weight_size; ++i) {
		for (int j = 0; j <= backpack_capacity; ++j) {
			if (j >= weight_bars[i]) {
				dp_max_mass[i][j] = std::max(dp_max_mass[i - 1][j], weight_bars[i] + dp_max_mass[i - 1][j - weight_bars[i]]);
			} else {
				dp_max_mass[i][j] = dp_max_mass[i - 1][j];
			}
		}
	}

	return dp_max_mass[weight_size - 1][backpack_capacity];
}

int Compute1DpMaxGoldMass(const std::vector<int>& weight_bars, int backpack_capacity) {
	/*
		Time Complexity: O(N * M) N - number of bars, M - backpack_capacity
		Memory Complexity: O(M)
	*/
	std::vector<int> prev(backpack_capacity + 1, 0);
	std::vector<int> current(backpack_capacity + 1, 0);

	for (size_t i = 1; i < weight_bars.size(); ++i) {
		for (size_t j = 0; j < current.size(); ++j) {
			if (j >= (size_t)weight_bars[i]) {
				current[j] = std::max(weight_bars[i] + prev[j - weight_bars[i]], prev[j]);
			} else {
				current[j] = prev[j];
			}
		}

		prev.swap(current);
	}

	return prev[backpack_capacity];
}

int main() {
	int gold_bars, backpack_capacity;
	std::cin >> gold_bars >> backpack_capacity;

	std::vector<int> weight_bars(gold_bars + 1, 0);
	for (int idx_bar = 1; idx_bar <= gold_bars; ++idx_bar) {
		std::cin >> weight_bars[idx_bar];
	}

	auto two_dp_max_gold = Compute2DpMaxGoldMass(weight_bars, backpack_capacity);
	auto one_dp_max_gold = Compute1DpMaxGoldMass(weight_bars, backpack_capacity);

	std::cout << two_dp_max_gold << '\n' << one_dp_max_gold << '\n';
}