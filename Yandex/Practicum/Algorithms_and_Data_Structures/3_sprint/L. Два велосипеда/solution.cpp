#include <iostream>
#include <vector>

int Solution(const std::vector<size_t>& money_per_days,
	size_t bike_price, size_t left, size_t right) {

	if (left == right) {
		if (left < money_per_days.size() && money_per_days[left] >= bike_price) {
			return static_cast<int>(left + 1);
		}
		return -1;
	}

	size_t mid = left + (right - left) / 2;

	if (money_per_days[mid] >= bike_price) {
		return Solution(money_per_days, bike_price, left, mid);
	} else {
		return Solution(money_per_days, bike_price, mid + 1, right);
	}
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

	int day_one = Solution(money_per_days, bike_price, left, right);
	int day_two = Solution(money_per_days, two_bikes_price, left, right);

	std::cout << day_one << ' ' << day_two << '\n';
}