#include <cctype>
#include <iostream>
#include <string>
#include <string_view>

void Solution(std::string_view line) {
	/*
		Time Complexity: O(L) L - text length
		Memory Complexity: O(1)
	*/

	bool is_palindrom = true;
	int16_t begin = 0;
	int16_t end = line.size() - 1;

	while (begin < end) {

		while (begin < end && !std::isalnum(static_cast<unsigned char>(line[begin]))) {
			++begin;
		}

		while (begin < end && !std::isalnum(static_cast<unsigned char>(line[end]))) {
			--end;
		}

		if (std::tolower(static_cast<unsigned char>(line[begin])) !=
			std::tolower(static_cast<unsigned char>(line[end]))) {
			is_palindrom = false;
			break;
		}

		++begin;
		--end;
	}
	std::cout << (is_palindrom ? "True" : "False") << '\n';
}

int main() {
	std::string text;
	std::getline(std::cin, text);

	Solution(text);
}