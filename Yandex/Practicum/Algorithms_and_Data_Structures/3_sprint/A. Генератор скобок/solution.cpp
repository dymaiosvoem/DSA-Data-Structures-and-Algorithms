#include <iostream>
#include <string>

void Solution(size_t open, size_t close, size_t bracket_sequence,
	std::string prefix) {
	/*
		Time Complexity: T(B) B - bracket_sequence
		Memory Complexity: T(B^2) B - bracket_sequence
	*/
	if ((open == close) && (close == bracket_sequence)) {
		std::cout << prefix << '\n';
	} else {
		if (open < bracket_sequence) {
			Solution(open + 1, close, bracket_sequence, prefix + "(");
			if (open > close) {
				Solution(open, close + 1, bracket_sequence, prefix + ")");
			}
		} else {
			Solution(open, close + 1, bracket_sequence, prefix + ")");
		}
	}
}

int main() {
	size_t bracket_sequence;
	std::cin >> bracket_sequence;

	Solution(0, 0, bracket_sequence, "");
}