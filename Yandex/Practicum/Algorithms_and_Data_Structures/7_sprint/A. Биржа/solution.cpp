#include <algorithm>
#include <iostream>

void Solution(size_t days) {
	/*
		Time Complexity: O(N)
		Memory Complexity: O(1)
	*/
	int prev_stock_price;

	if (days != 0) {
		std::cin >> prev_stock_price;
	}

	int max_profit = 0;

	for (size_t i = 1; i < days; ++i) {
		int stock_price;
		std::cin >> stock_price;

		max_profit += std::max(stock_price - prev_stock_price, 0);
		prev_stock_price = stock_price;
	}

	std::cout << max_profit << '\n';
}

int main() {
	size_t days;
	std::cin >> days;

	Solution(days);
}