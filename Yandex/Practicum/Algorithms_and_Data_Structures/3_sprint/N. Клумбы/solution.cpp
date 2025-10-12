#include <algorithm>
#include <iostream>
#include <vector>

struct Bed {
	size_t start;
	size_t end;
};

bool compare_beds_coordinates(const Bed& left, const Bed& right) {
	return (left.start < right.start) || (left.start == right.start && left.end < right.end);
}

std::vector<Bed> MergeSortBeds(std::vector<Bed>& flower_beds, bool (*less)(const Bed&, const Bed&)) {
	/*
		Time Complexity: T(N * log N)
		Memory Complexity: O(N)
	*/
	if (flower_beds.size() <= 1) {
		return flower_beds;
	}

	size_t mid = flower_beds.size() / 2;

	std::vector<Bed> left(flower_beds.begin(), flower_beds.begin() + mid);
	left = MergeSortBeds(left, less);

	std::vector<Bed> right(flower_beds.begin() + mid, flower_beds.end());
	right = MergeSortBeds(right, less);

	std::vector<Bed> result(flower_beds.size());

	size_t l = 0, r = 0, k = 0;

	while (l < left.size() && r < right.size()) {
		if (!less(right[r], left[l])) {
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
		++k;
		++l;
	}

	while (r < right.size()) {
		result[k] = right[r];
		++k;
		++r;
	}

	return result;
}

std::vector<Bed> MergeBeds(const std::vector<Bed>& sorted_flower_beds) {
	/*
		Time Complexity: O(N)
		Memory Complexity: O(N)
	*/
	std::vector<Bed> result;
	result.reserve(sorted_flower_beds.size());

	Bed current = sorted_flower_beds[0];

	for (size_t i = 1; i < sorted_flower_beds.size(); ++i) {
		if (current.end >= sorted_flower_beds[i].start) {
			current.end = std::max(current.end, sorted_flower_beds[i].end);
		} else {
			result.push_back(current);
			current = sorted_flower_beds[i];
		}
	}

	result.push_back(current);

	return result;
}

void PrintBeds(const std::vector<Bed>& sorted_flower_beds) {
	for (const auto& bed : sorted_flower_beds) {
		std::cout << bed.start << ' ' << bed.end << '\n';
	}
}

int main() {
	size_t gardeners;
	std::cin >> gardeners;

	std::vector<Bed> flower_beds(gardeners);
	for (size_t i = 0; i < gardeners; ++i) {
		std::cin >> flower_beds[i].start >> flower_beds[i].end;
	}

	/*
		Time Complexity: T(N * log N) + O(N) = T(N* log N)
		Memory Complexity: O(N) + O(N) = O(N)
	*/

	std::vector<Bed> sorted_flower_beds = MergeSortBeds(flower_beds, compare_beds_coordinates);

	const std::vector<Bed> merged_beds = MergeBeds(sorted_flower_beds);

	PrintBeds(merged_beds);
}