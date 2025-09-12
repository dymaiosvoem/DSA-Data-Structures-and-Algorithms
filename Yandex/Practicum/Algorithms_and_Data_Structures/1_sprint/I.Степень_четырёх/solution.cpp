#include <cmath>
#include <iostream>

void Solution(uint16_t num) {
	/*
		Time Complexity: O(1)
		Memory Complexity: O(1)
	*/
	bool is_degree = false;

	for (size_t i = 0; i < 7; ++i) {
		uint16_t result = static_cast<uint16_t>(std::pow(4, i));

		if (result == num) {
			is_degree = true;
			break;
		}
	}
	std::cout << (is_degree ? "True" : "False") << std::endl;
}

int main() {
	uint16_t number;
	std::cin >> number;

	Solution(number);
}