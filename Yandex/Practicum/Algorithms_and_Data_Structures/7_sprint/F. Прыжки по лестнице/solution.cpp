#include <iostream>
#include <vector>

const long long MOD = 1'000'000'007;

void SolveJumpingOnStairs(size_t steps, size_t max_jump) {
	/*
		Time Complexity: O(S * J) S - steps, J - max_jump
		Memory Complexity: O(R)
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

int main() {
	size_t steps, max_jump;
	std::cin >> steps >> max_jump;

	SolveJumpingOnStairs(steps, max_jump);
}