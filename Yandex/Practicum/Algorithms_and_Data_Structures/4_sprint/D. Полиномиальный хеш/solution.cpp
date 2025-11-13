#include <iostream>
#include <string>

void Solution(size_t base, size_t module, const std::string& s) {
	/*
		Time Complexity: O(N)
		Memory Complexity: O(1)
	*/
	size_t hash = 0;

	for (char ch : s) {
		hash = (hash * base + static_cast<size_t>(ch)) % module;
	}

	std::cout << hash << '\n';
}

int main() {
	size_t base, module;
	std::cin >> base >> module;

	std::string s;
	std::cin >> s;

	Solution(base, module, s);
}