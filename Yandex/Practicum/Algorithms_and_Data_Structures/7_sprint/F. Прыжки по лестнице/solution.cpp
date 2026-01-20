#include <iostream>
#include <vector>

const long long MOD = 1'000'000'007;

void NaiveSolveJumpingOnStairs(size_t steps, size_t max_jump) {
	/*
		Time Complexity: O(S * J) S - steps, J - max_jump
		Memory Complexity: O(S)
	*/
	std::vector<long long> dp_ways(steps + 1, 0);
	dp_ways[1] = 1;

	for (size_t step = 1; step < steps; ++step) {
		for (size_t jump_len = 1; jump_len <= max_jump && step + jump_len <= steps; ++jump_len) {
			dp_ways[step + jump_len] = (dp_ways[step] + dp_ways[step + jump_len]) % MOD;
		}
	}

	std::cout << dp_ways[steps] << '\n';
}

void FastSolveJumpingOnStairs(size_t steps, size_t max_jump) {
	/*
		Time Complexity: O(1)
		Memory Complexity: O(S) S - steps
	*/
	std::vector<long long> dp_ways(steps + 1, 0);
	dp_ways[1] = 1;

	long long S = dp_ways[1];

	for (int step = 2; step <= (int)steps; ++step) {
		dp_ways[step] = S;

		S += dp_ways[step];
		S %= MOD;

		int out_idx = step - max_jump;

		if (out_idx >= 1) {
			S -= dp_ways[out_idx];
			S %= MOD;

			if (S < 0) {
				S += MOD;
			}
		}
	}

	std::cout << dp_ways[steps] << '\n';
}

int main() {
	size_t steps, max_jump;
	std::cin >> steps >> max_jump;

	NaiveSolveJumpingOnStairs(steps, max_jump);
	FastSolveJumpingOnStairs(steps, max_jump);
}