#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

size_t ComputeLevenshteinDistance(std::string_view s, std::string_view t) {
	size_t s_size = s.size(), t_size = t.size();

	if (s_size == 0 || t_size == 0) {
		return std::max(s_size, t_size);
	}

	std::vector<std::vector<size_t>> dp(s_size + 1, std::vector<size_t>(t_size + 1, 0));

	for (size_t i = 0; i <= s_size; ++i) {
		for (size_t j = 0; j <= t_size; ++j) {
			if (i == 0) {

			}
			if (s[i - 1] == t[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				size_t symbol_replacement = dp[i - 1][j - 1] + 1;
				size_t symbol_inserting = dp[i][j - 1] + 1;
				size_t symbol_deleting = dp[i - 1][j] + 1;

				dp[i][j] = std::max({ symbol_replacement , symbol_inserting, symbol_deleting });
			}
		}
	}

	return dp[s_size][t_size];
}

int main() {
	std::string s, t;
	std::cin >> s >> t;

	auto distance = ComputeLevenshteinDistance(s, t);
	std::cout << distance << '\n';
}