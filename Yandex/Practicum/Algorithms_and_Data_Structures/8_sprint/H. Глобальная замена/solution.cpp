#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> SearchAllPatternStartIndicesInText(const std::string& text, const std::string& pattern) {
	/*
		T = text.length(), P = pattern.length();
		Time Complexity: O(T + P + T) = O(T + P);
		Memory Complexity: O(T + P);
	*/
	std::vector<size_t> result;

	std::string combined_str = pattern + '#' + text;

	std::vector<size_t> pi(pattern.length(), 0);
	size_t match_length = 0;

	for (size_t i = 1; i < combined_str.length(); ++i) {
		size_t k = match_length;

		while (k > 0 && combined_str[k] != combined_str[i]) {
			k = pi[k - 1];
		}

		if (combined_str[k] == combined_str[i]) {
			++k;
		}

		if (i < pattern.length()) {
			pi[i] = k;
		}

		match_length = k;
		if (k == pattern.length()) {
			result.push_back(i - 2 * pattern.length());
		}
	}

	return result;
}

void BuildAndPrintModifiedText(const std::vector<size_t>& indices, const std::string& text,
	const std::string& pattern, const std::string& pattern_substitution) {
	size_t p = pattern.length();
	size_t indices_idx = 0;

	for (size_t i = 0; i < text.length(); ) {
		if (indices_idx < indices.size() && i == indices[indices_idx]) {
			std::cout << pattern_substitution;

			i += p;
			++indices_idx;
		} else {
			std::cout << text[i];

			++i;
		}
	}

	std::cout << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string text, pattern, pattern_substitution;
	std::cin >> text >> pattern >> pattern_substitution;

	auto indices = SearchAllPatternStartIndicesInText(text, pattern);
	BuildAndPrintModifiedText(indices, text, pattern, pattern_substitution);
}
