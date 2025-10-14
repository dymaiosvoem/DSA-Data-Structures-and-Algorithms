#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

std::tuple<std::vector<size_t>, std::vector<size_t>, std::vector<size_t>> partition(const std::vector<size_t>& container, size_t pivot) {
	std::vector<size_t> left, mid, right;

	for (const auto& elem : container) {
		if (elem < pivot) {
			left.push_back(elem);
		} else if (elem == pivot) {
			mid.push_back(elem);
		} else {
			right.push_back(elem);
		}
	}

	return { left, mid, right };
}

std::vector<size_t> QuickSort(const std::vector<size_t>& container) {
	if (container.size() <= 1) {
		return container;
	}

	size_t pivot = container[rand() % container.size()];
	auto [left, mid, right] = partition(container, pivot);

	auto sorted_left = QuickSort(left);
	auto sorted_right = QuickSort(right);

	std::vector<size_t> result;
	result.reserve(sorted_left.size() + mid.size() + sorted_right.size());

	result.insert(result.end(), sorted_left.begin(), sorted_left.end());
	result.insert(result.end(), mid.begin(), mid.end());
	result.insert(result.end(), sorted_right.begin(), sorted_right.end());

	return result;
}

void QuickSortSolution(std::vector<size_t>& greed_children, std::vector<size_t>& size_cookies) {
	/*
		Time Complexity: T(N log N + M log M); Worse: T(N^2 + M^2)
		Memory Complexity: O(N + M)
	*/
	std::vector<size_t> sorted_greed = QuickSort(greed_children);
	std::vector<size_t> sorted_size = QuickSort(size_cookies);

	size_t greed = 0, size = 0, result = 0;
	while (greed < sorted_greed.size() && size < sorted_size.size()) {
		if (sorted_greed[greed] <= sorted_size[size]) {
			++result;
			++greed;
		}
		++size;
	}

	std::cout << result << '\n';
}

void CountSortSolution(const std::vector<size_t>& greed_children, const std::vector<size_t>& size_cookies) {
	/*
		Time Complexity: O(G + C + S) G - greed_children, C - size_cookies, S - size
		Memory Complexity: O(S)
	*/
	size_t max_value_greed = *std::max_element(greed_children.begin(), greed_children.end());
	size_t max_value_size_cookies = *std::max_element(size_cookies.begin(), size_cookies.end());
	size_t S = std::max(max_value_greed, max_value_size_cookies) + 1;

	std::vector<size_t> sorted_greed(S), sorted_cookies(S);

	for (size_t i = 0; i < greed_children.size(); ++i) {
		++sorted_greed[greed_children[i]];
	}

	for (size_t i = 0; i < size_cookies.size(); ++i) {
		++sorted_cookies[size_cookies[i]];
	}

	size_t need = 0, result = 0;

	for (size_t i = 0; i < S; ++i) {
		need += sorted_greed[i];
		size_t take = std::min(need, sorted_cookies[i]);
		result += take;
		need -= take;
	}

	std::cout << result << '\n';
}

int main() {
	size_t count_children;
	std::cin >> count_children;

	std::vector<size_t> greed_children(count_children);
	for (size_t i = 0; i < count_children; ++i) {
		std::cin >> greed_children[i];
	}

	size_t count_cookies;
	std::cin >> count_cookies;

	std::vector<size_t> size_cookies(count_cookies);
	for (size_t i = 0; i < count_cookies; ++i) {
		std::cin >> size_cookies[i];
	}

	QuickSortSolution(greed_children, size_cookies);
	CountSortSolution(greed_children, size_cookies);
}