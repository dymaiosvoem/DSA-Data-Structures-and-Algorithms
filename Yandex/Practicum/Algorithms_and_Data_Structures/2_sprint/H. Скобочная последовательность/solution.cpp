#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void is_correct_bracket_seq(std::string_view str) {
	/*
		Time Commplexity: O(L) L = length str
		Memory Complexity: O(L) Saving str to stack
	*/
	if (str.size() % 2 != 0) {
		std::cout << "False" << '\n';
		return;
	}

	size_t str_size = str.size();

	std::vector<char> stack;
	stack.reserve(str_size);

	bool is_correct = true;

	for (size_t i = 0; i < str_size; ++i) {
		char ch = str[i];

		switch (ch) {
		case '(':
			stack.push_back(')');
			continue;
		case '{':
			stack.push_back('}');
			continue;
		case '[':
			stack.push_back(']');
			continue;
		default:
			if (!stack.empty() && stack.back() == ch) {
				stack.pop_back();
				continue;
			}

			is_correct = false;
			break;
		}
	}

	std::cout << (is_correct && stack.empty() ? "True" : "False") << '\n';
}

int main() {
	std::string str;
	std::cin >> str;

	is_correct_bracket_seq(str);
}