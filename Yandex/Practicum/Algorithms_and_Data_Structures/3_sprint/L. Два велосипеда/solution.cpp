#include <iostream>
#include <vector>

int RecursiveSolution(const std::vector<size_t>& money_per_days,
	size_t bike_price, size_t left, size_t right) {
	/*
		Time Complexity: T(log N) N - size of money_per_days
		Memory Complexity: T(log N)
	*/
	if (left == money_per_days.size()) {
		return -1;
	}

	if (money_per_days[left] >= bike_price) {
		return left + 1;
	}

	size_t mid = left + (right - left) / 2;

	if (money_per_days[mid] >= bike_price) {
		return RecursiveSolution(money_per_days, bike_price, left, mid);
	}

	if (money_per_days[mid] < bike_price) {
		return RecursiveSolution(money_per_days, bike_price, mid + 1, right);
	}
}

int IterativeSolution(const std::vector<size_t>& money_per_days,
	size_t bike_price, size_t left, size_t right) {
	/*
		Time Complexity: O(log N) N - size of money_per_days
		Memory Complexity: O(1)
	*/
	while (left < right) {
		size_t mid = left + (right - left) / 2;

		if (money_per_days[mid] >= bike_price) {
			right = mid;
			continue;
		} else {
			left = mid + 1;
			continue;
		}

	}

	return left == money_per_days.size() ? -1 : left + 1;
}

int main() {
	size_t days_saving;
	std::cin >> days_saving;

	std::vector<size_t> money_per_days;
	money_per_days.reserve(days_saving);

	for (size_t start = 0; start < days_saving; ++start) {
		size_t count_money;
		std::cin >> count_money;

		money_per_days.push_back(count_money);
	}

	size_t bike_price;
	std::cin >> bike_price;

	size_t two_bikes_price = bike_price * 2;
	size_t left = 0;
	size_t right = money_per_days.size();

	int day_one = RecursiveSolution(money_per_days, bike_price, left, right);
	int day_two = IterativeSolution(money_per_days, two_bikes_price, left, right);

	std::cout << day_one << ' ' << day_two << '\n';
}