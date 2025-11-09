#include <algorithm>
#include <iostream>
#include <unordered_map>

/*
	10 --- size
	 0   0   1   0   1   1   1   0   0   0 --- input
	-1  -1  +1  -1  +1  +1  +1  -1  -1  -1 --- value
  0 -1  -2  -1  -2  -1   0   1   0  -1  -2 --- first
	 1   2   3   4   5   6   7   8   9  10 --- idx
*/

void Solution(size_t n) {
	std::unordered_map<int, size_t> first(n + 1);
	first[0] = 0;

	size_t i = 1, result = 0;
	int sum = 0;

	while (i <= n) {
		int x;
		std::cin >> x;

		int value = (x == 0 ? -1 : 1);
		sum += value;

		if (first.find(sum) != first.end()) {
			result = std::max(result, i - first[sum]);
		} else {
			first[sum] = i;
		}

		++i;
	}
	std::cout << result << '\n';
}

int main() {
	size_t n;
	std::cin >> n;

	Solution(n);
}