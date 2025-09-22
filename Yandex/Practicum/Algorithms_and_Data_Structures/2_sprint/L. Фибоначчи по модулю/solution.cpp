#include <iostream>

void Solution(size_t intern_number, size_t number_in_power) {
	/*
		Time Complexity: O(N) N - intern number
		Memory Complexity: O(1)
	*/
	size_t first_intern = 1 % number_in_power, second_intern = 1 % number_in_power;
	size_t result = 1 % number_in_power;

	for (size_t i = 1; i < intern_number; ++i) {
		result = (first_intern + second_intern) % number_in_power;
		first_intern = second_intern;
		second_intern = result;
	}

	std::cout << result << '\n';
}

int main() {
	size_t intern_number, degree;
	std::cin >> intern_number >> degree;

	size_t number_in_power = 1;

	for (size_t i = 0; i < degree; ++i) {
		number_in_power *= 10;
	}

	Solution(intern_number, number_in_power);
}