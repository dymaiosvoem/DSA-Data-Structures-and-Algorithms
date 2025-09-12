#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void Solution(std::vector<unsigned int>& vec) {
	/*
		Time Complexity: O(L) L - street length
		Memory Complexity: O(1)
	*/
	auto first_zero = vec.begin();
	auto end = vec.end();

	while (first_zero != end && *first_zero != 0) {
		*first_zero = 1u << 20;
		++first_zero;
	}

	for (auto start = first_zero; start != end; ++start) {
		if (*start == 0) {
			continue;
		}

		*start = *std::prev(start) + 1;
	}

	for (auto start = end - 1; start != vec.begin(); ) {
		--start;

		*start = std::min(*std::next(start) + 1, *start);
	}
}

int main() {
	size_t street_length;
	std::cin >> street_length;

	std::vector<unsigned int> house_numbers;
	house_numbers.reserve(street_length);

	for (size_t i = 0; i < street_length; ++i) {
		unsigned int num;
		std::cin >> num;
		house_numbers.emplace_back(num);
	}

	Solution(house_numbers);

	bool space = true;
	for (auto& num : house_numbers) {
		if (space) {
			std::cout << num;
			space = false;
			continue;
		}
		std::cout << ' ' << num;
	}
}