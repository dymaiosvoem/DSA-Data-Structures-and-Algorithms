#include <array>
#include <iostream>
#include <string>

void Solution(const std::array<std::string, 10>& letters, const std::string& numbers,
	size_t step, std::string& prefix) {
	/*
		Time Complexity: T(N)
		Memory Complexity: T(N)
	*/
	if (step == numbers.size()) {
		std::cout << prefix << ' ';
	} else {
		char number = numbers[step];
		size_t start = 0;

		while (start < letters[number - '0'].size()) {
			prefix.push_back(letters[number - '0'][start]);

			Solution(letters, numbers, step + 1, prefix);

			prefix.pop_back();
			++start;
		}
	}
}

int main() {
	std::array<std::string, 10> letters = { "", "", "abc", "def", "ghi",
										   "jkl", "mno", "pqrs",
										   "tuv", "wxyz" };
	std::string numbers;
	std::cin >> numbers;

	std::string prefix;
	prefix.reserve(numbers.size());

	Solution(letters, numbers, 0, prefix);
}