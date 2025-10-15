#include <algorithm>
#include <iostream>
#include <vector>

std::vector<size_t> MergeSort(const std::vector<size_t>& house_prices) {
	/*
		Time Complexity: T(N * log N)
		Memory Complexity: O(N)
	*/
	if (house_prices.size() <= 1) {
		return house_prices;
	}

	size_t mid = house_prices.size() / 2;

	std::vector<size_t> left(house_prices.begin(), house_prices.begin() + mid);
	left = MergeSort(left);

	std::vector<size_t> right(house_prices.begin() + mid, house_prices.end());
	right = MergeSort(right);

	std::vector<size_t> result(left.size() + right.size());
	size_t l = 0, r = 0, k = 0;

	while (l < left.size() && r < right.size()) {
		if (left[l] <= right[r]) {
			result[k] = left[l];
			++l;
		} else {
			result[k] = right[r];
			++r;
		}

		++k;
	}

	while (l < left.size()) {
		result[k] = left[l];
		++l;
		++k;
	}

	while (r < right.size()) {
		result[k] = right[r];
		++r;
		++k;
	}

	return result;
}

void MergeSortSolution(const std::vector<size_t>& house_prices, size_t purchase_budget) {
	std::vector<size_t> sorted_prices = MergeSort(house_prices);

	size_t start = 0, result = 0;
	while (start < sorted_prices.size() && sorted_prices[start] <= purchase_budget) {
		++result;
		purchase_budget -= sorted_prices[start];
		++start;
	}

	std::cout << result << '\n';
}

void CountSortSolution(const std::vector<size_t>& house_prices, size_t purchase_budget) {
	/*
		Time Complexity: O(N + S) N - house_prices.size(), S - sorted_prices.size()
		Memory Complextiry: O(S)
	*/
	std::vector<size_t> freq_prices(100001);

	for (size_t i = 0; i < house_prices.size(); ++i) {
		++freq_prices[house_prices[i]];
	}

	size_t start = 1, result = 0;
	while (start < freq_prices.size() && start <= purchase_budget) {
		if (start <= purchase_budget && freq_prices[start] != 0) {
			size_t buy = std::min(freq_prices[start], purchase_budget / start);
			result += buy;
			purchase_budget -= buy * start;
			freq_prices[start] -= buy;
		}
		++start;
	}

	std::cout << result << '\n';
}

int main() {
	size_t count_house_in_question, purchase_budget;
	std::cin >> count_house_in_question >> purchase_budget;

	std::vector<size_t> house_prices(count_house_in_question);
	for (size_t i = 0; i < count_house_in_question; ++i) {
		std::cin >> house_prices[i];
	}

	MergeSortSolution(house_prices, purchase_budget);
	CountSortSolution(house_prices, purchase_budget);
}