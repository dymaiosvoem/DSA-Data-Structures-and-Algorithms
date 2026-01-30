/*
	-- ПРИНЦИП РАБОТЫ --

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

*/

#include <iostream>
#include <vector>

bool HasEqualSubsetPartition(const std::vector<int>& points, int total) {
	if (total % 2 != 0) {
		return false;
	}

	int half = total / 2;

	std::vector<bool> dp_achievable(half + 1, false);
	dp_achievable[0] = true;

	for (int i = 0; i < static_cast<int>(points.size()); ++i) {
		for (int j = half; j >= 0; --j) {

			if (!dp_achievable[j]) {
				continue;
			}

			int next_sum = points[i] + j;

			if (next_sum <= half) {
				if (next_sum == half) {
					return true;
				}

				dp_achievable[next_sum] = true;
			}
		}
	}

	return dp_achievable[half];
}

int main() {
	size_t n;
	std::cin >> n;

	std::vector<int> points(n, 0);
	int total = 0;

	for (size_t i = 0; i < n; ++i) {
		std::cin >> points[i];

		total += points[i];
	}

	if (HasEqualSubsetPartition(points, total)) {
		std::cout << "True" << '\n';
	} else {
		std::cout << "False" << '\n';
	}
}