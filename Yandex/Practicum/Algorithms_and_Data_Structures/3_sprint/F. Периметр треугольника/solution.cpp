#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

using Tuple = std::tuple< std::vector<size_t>, std::vector<size_t>, std::vector<size_t>>;

Tuple partition(const std::vector<size_t>& segment_lengths, size_t pivot) {
	std::vector<size_t> left, mid, right;

	for (const auto& s : segment_lengths) {
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

std::vector<size_t> QuickSort(const std::vector<size_t>& segment_lengths) {
	if (segment_lengths.size() <= 1) {
		return segment_lengths;
	}

	size_t pivot = segment_lengths[rand() % segment_lengths.size()];
	auto [left, mid, right] = partition(segment_lengths, pivot);

	left = QuickSort(left);
	right = QuickSort(right);

	std::vector<size_t> result(left.begin(), left.end());
	result.insert(result.end(), mid.begin(), mid.end());
	result.insert(result.end(), right.begin(), right.end());

	return result;
}

void Solution(const std::vector<size_t>& segment_lengths) {
	/*
		Time Complexity: T(N * log N); Worse T(N^2)
		Memory Complexity: O(N)
	*/
	std::vector<size_t> sorted_segment_lengths = QuickSort(segment_lengths);

	size_t last_segment = sorted_segment_lengths.size() - 1, result = 0;

	for (size_t l = last_segment; l >= 2; --l) {
		size_t a = sorted_segment_lengths[l - 2], b = sorted_segment_lengths[l - 1], c = sorted_segment_lengths[l];
		if (a + b > c) {
			result = a + b + c;
			break;
		}
	}

	std::cout << result << '\n';
}

int main() {
	size_t count_segments;
	std::cin >> count_segments;

	std::vector<size_t> segment_lengths(count_segments);
	for (size_t i = 0; i < segment_lengths.size(); ++i) {
		std::cin >> segment_lengths[i];
	}

	Solution(segment_lengths);
}