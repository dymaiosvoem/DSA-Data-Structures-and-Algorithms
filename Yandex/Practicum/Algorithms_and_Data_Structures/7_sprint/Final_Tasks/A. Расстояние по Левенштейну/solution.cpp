#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

size_t ComputeLevenshteinDistance(const std::string& s, const std::string& t) {
	size_t s_size = s.size(), t_size = t.size();

	std::vector<std::vector<size_t>> dp_dist(s_size + 1, std::vector<size_t>(t_size + 1, 0));

	std::iota(dp_dist[0].begin(), dp_dist[0].end(), 0);

	for (size_t k = 1; k <= s_size; ++k) {
		dp_dist[k][0] = k;
	}

	for (size_t i = 1; i <= s_size; ++i) {
		for (size_t j = 1; j <= t_size; ++j) {
			if (s[i - 1] == t[j - 1]) {
				dp_dist[i][j] = dp_dist[i - 1][j - 1];
			} else {
				dp_dist[i][j] = std::min({ dp_dist[i - 1][j] + 1, dp_dist[i][j - 1] + 1, dp_dist[i - 1][j - 1] + 1 });
			}
		}
	}

	return dp_dist[s_size][t_size];
}

int main() {
	std::string s, t;
	std::cin >> s >> t;

	auto distance = ComputeLevenshteinDistance(s, t);
	std::cout << distance << '\n';
}