#include <iostream>
#include <string>
#include <vector>

void CombineAndPrintStrings(std::string& s, size_t gift_strings) {
	/*
		Time Complexity: O(N), N - pocket.size()
		Memory Complexity: O(N)
	*/
	std::vector<std::string> mapping_ki_to_ti(s.size() + 1, "");

	for (size_t i = 0; i < gift_strings; ++i) {
		std::string t_i;
		size_t k_i;

		std::cin >> t_i >> k_i;

		mapping_ki_to_ti[k_i] = t_i;
	}

	for (size_t j = 0; j < mapping_ki_to_ti.size(); ++j) {
		if (mapping_ki_to_ti[j] != "") {
			std::cout << mapping_ki_to_ti[j];
		}

		if (j < s.size()) {
			std::cout << s[j];
		}
	}

	std::cout << '\n';
}

int main() {
	std::string str;
	std::cin >> str;

	size_t gift_strings;
	std::cin >> gift_strings;

	CombineAndPrintStrings(str, gift_strings);
}