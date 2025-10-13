#include <iostream>
#include <vector>

void Solution(const std::vector<size_t>& colors_for_items, size_t count_items_in_wardrobe,
	size_t count_colors) {
	/*
		Time Complexity: O(N) N - count_items_in_wardrobe
		Memory Complexity: O(C) C - count_colors
	*/
	std::vector<size_t> result(count_colors);

	for (size_t i = 0; i < count_items_in_wardrobe; ++i) {
		size_t value = colors_for_items[i];
		++result[value];
	}

	size_t value_color = 0;

	for (size_t i = 0; i < result.size(); ++i) {
		for (size_t j = 0; j < result[i]; ++j) {
			std::cout << value_color << ' ';
		}
		++value_color;
	}
}

int main() {
	size_t count_items_in_wardrobe;
	std::cin >> count_items_in_wardrobe;

	size_t count_colors = 3;

	std::vector<size_t> colors_for_items(count_items_in_wardrobe);
	for (size_t i = 0; i < colors_for_items.size(); ++i) {
		std::cin >> colors_for_items[i];
	}

	Solution(colors_for_items, count_items_in_wardrobe, count_colors);
}