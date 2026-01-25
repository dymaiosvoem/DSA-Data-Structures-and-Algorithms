#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void RestoreAndPrintLcsIndices(const std::vector<std::vector<size_t>>& dp, const std::vector<size_t>& A_sequence, const std::vector<size_t>& B_sequence) {
	int iA = (int)A_sequence.size() - 1, jB = (int)B_sequence.size() - 1;
	size_t max_length = dp[iA][jB];

	std::cout << max_length << '\n';

	std::stack<size_t> A_lcs_indices, B_lcs_indices;
	while (iA > 0 && jB > 0) {
		if (A_sequence[iA] == B_sequence[jB] &&
			dp[iA][jB] == dp[iA - 1][jB - 1] + 1) {
			A_lcs_indices.push(iA);
			B_lcs_indices.push(jB);

			--iA;
			--jB;
		} else {
			if (dp[iA - 1][jB] >= dp[iA][jB - 1]) {
				--iA;
			} else {
				--jB;
			}
		}
	}

	bool space = false;

	while (!A_lcs_indices.empty()) {
		if (space) {
			std::cout << ' ' << A_lcs_indices.top();
		} else {
			std::cout << A_lcs_indices.top();
			space = true;
		}

		A_lcs_indices.pop();
	}

	std::cout << '\n';
	space = false;

	while (!B_lcs_indices.empty()) {
		if (space) {
			std::cout << ' ' << B_lcs_indices.top();
		} else {
			std::cout << B_lcs_indices.top();
			space = true;
		}

		B_lcs_indices.pop();
	}

	std::cout << '\n';
}

std::vector<std::vector<size_t>> ComputeLcsDp(const std::vector<size_t>& A_sequence, const std::vector<size_t>& B_sequence) {
	std::vector<std::vector<size_t>> dp(A_sequence.size(), std::vector<size_t>(B_sequence.size(), 0));

	for (size_t i = 1; i < A_sequence.size(); ++i) {
		for (size_t j = 1; j < B_sequence.size(); ++j) {
			if (A_sequence[i] == B_sequence[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp;
}

int main() {
	size_t n;
	std::cin >> n;

	std::vector<size_t> A_sequence(n + 1, 0);
	for (size_t i = 1; i <= n; ++i) {
		std::cin >> A_sequence[i];
	}

	size_t m;
	std::cin >> m;

	std::vector<size_t> B_sequence(m + 1, 0);
	for (size_t j = 1; j <= m; ++j) {
		std::cin >> B_sequence[j];
	}

	/*
		Time Complexity: 
			ComputeLcsDp - O(n * m)
			RestoreAndPrintLcsIndices - O(n + m)
		Memory Complexity:
			dp - O(n * m)
			A_sequence, B_sequence - O(n + m)
			A_lcs_indices, B_lcs_indices - L <= min(n,m) - O(2L)
	*/
	auto dp = ComputeLcsDp(A_sequence, B_sequence);
	RestoreAndPrintLcsIndices(dp, A_sequence, B_sequence);
}