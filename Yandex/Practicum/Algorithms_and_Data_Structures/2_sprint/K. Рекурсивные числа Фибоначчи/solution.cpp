#include <iostream>
#include <unordered_map>

size_t Solution(size_t intern_number, std::unordered_map<size_t, size_t>& memo) {
	/*
		Time Complexity: T(N) N - count recursion
		Memory Complexity: O(M) M - memo size
	*/
	auto it = memo.find(intern_number);

	if (it != memo.end()) {
		return it->second;
	}

	memo[intern_number] = Solution(intern_number - 1, memo) + Solution(intern_number - 2, memo);

	return memo[intern_number];
}

int main() {
	size_t intern_number;
	std::cin >> intern_number;

	std::unordered_map<size_t, size_t> memo = { { 0, 1 }, {1, 1} };
	memo.reserve(intern_number + 1);

	size_t result = Solution(intern_number, memo);

	std::cout << result << '\n';
}