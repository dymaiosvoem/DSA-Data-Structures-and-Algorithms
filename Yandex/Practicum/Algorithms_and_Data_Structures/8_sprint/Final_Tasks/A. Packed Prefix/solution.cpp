#include <algorithm>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

std::string DecodePackedString(const std::string& packed_str) {
	std::stack<std::pair<std::string, size_t>> stack;

	std::string current;
	size_t repeat_count = 0;

	for (size_t i = 0; i < packed_str.length(); ++i) {
		char ch = packed_str[i];

		if (std::isdigit(ch)) {
			repeat_count = static_cast<size_t>(ch) - static_cast<size_t>('0');
		} else if (ch == '[') {
			stack.emplace(std::move(current), repeat_count);

			current.clear();
			repeat_count = 0;
		} else if (ch == ']') {
			auto [prev_str, prev_rep_count] = std::move(stack.top());
			stack.pop();

			prev_str.reserve(prev_str.length() + current.length() * prev_rep_count);

			for (size_t j = 0; j < prev_rep_count; ++j) {
				prev_str.append(current);
			}

			current = std::move(prev_str);
		} else {
			current.push_back(ch);
		}
	}

	return current;
}

void Solution(size_t n) {
	std::string packed_str;
	std::cin >> packed_str;

	std::string common_prefix = DecodePackedString(packed_str);

	for (size_t i = 1; i < n; ++i) {
		std::cin >> packed_str;

		std::string decoded_str = DecodePackedString(packed_str);

		size_t j = 0;
		const size_t min_length = std::min(common_prefix.length(), decoded_str.length());

		while (j < min_length && common_prefix[j] == decoded_str[j]) {
			++j;
		}

		common_prefix.resize(j);
	}

	std::cout << common_prefix << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t n;
	std::cin >> n;

	Solution(n);
}