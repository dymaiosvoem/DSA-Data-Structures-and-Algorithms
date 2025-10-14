#include <iostream>
#include <vector>

void Solution(const std::vector<size_t>& colors_for_items) {
	/*
		Time Complexity: O(N) N - colors_for_items.size()
		Memory Complexity: O(1) count colors - 3
	*/
	std::vector<size_t> result = { 0, 0, 0 };

	for (size_t i = 0; i < colors_for_items.size(); ++i) {
		++result[colors_for_items[i]];
	}

	bool printed_anything = false;

	for (size_t i = 0; i < result.size(); ++i) {
		for (size_t j = 0; j < result[i]; ++j) {
			if (!printed_anything) {
				std::cout << i;
				printed_anything = true;
				continue;
			}
			std::cout << ' ' << i;
		}
	}
}

int main() {
	size_t count_items_in_wardrobe;
	std::cin >> count_items_in_wardrobe;

	std::vector<size_t> colors_for_items(count_items_in_wardrobe);
	for (size_t i = 0; i < colors_for_items.size(); ++i) {
		std::cin >> colors_for_items[i];
	}

	Solution(colors_for_items);
}