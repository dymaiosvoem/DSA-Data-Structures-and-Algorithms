#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> PrefixFunctionKMP(const std::string& pattern) {
	/*
		n = pattern.length();
		Time Complexity: суммарно k увеличивается не более n раз = O(n);
						 суммарно откатов (0 <= k = pi[k - 1] <= n) = O(n).

						 Итог: O(2n) = O(n).
		Memory Complexity: O(l).
	*/
	size_t n = pattern.length();
	std::vector<size_t> pi(n, 0);

	for (size_t i = 1; i < n; ++i) {
		size_t k = pi[i - 1];

		while (k > 0 && pattern[k] != pattern[i]) {
			k = pi[k - 1];
		}

		if (pattern[k] == pattern[i]) {
			++k;
		}

		pi[i] = k;
	}

	return pi;
}

void PrintPi(const std::vector<size_t>& result) {
	for (size_t i = 0; i < result.size(); ++i) {
		if (i) {
			std::cout << ' ' << result[i];
		} else {
			std::cout << result[i];
		}
	}

	std::cout << '\n';
}

int main() {
	std::string pattern;
	std::cin >> pattern;

	auto pi = PrefixFunctionKMP(pattern);
	PrintPi(pi);
}