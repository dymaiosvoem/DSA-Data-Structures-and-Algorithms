#include <iostream>
#include <vector>

void Solution(size_t n) {
	/*
		Time Complexity: O(N^2)
		Memory Complexity: O(N)
	*/
	std::vector<size_t> T(n + 1);
	T[0] = 1;
	T[1] = 1;

	for (size_t k = 2; k <= n; ++k) {
		T[k] = 0;

		for (size_t i = 1; i <= k; ++i) {
			T[k] += T[i - 1] * T[k - i];
		}
	}

	std::cout << T[n] << '\n';
}

int main() {
	size_t n;
	std::cin >> n;

	Solution(n);
}