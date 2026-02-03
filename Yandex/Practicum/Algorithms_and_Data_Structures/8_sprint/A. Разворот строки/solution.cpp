#include <iostream>
#include <string>

std::string ConvertText(const std::string& str) {
	/*
		Time Complexity: O(N), N - str.size()
		Memory Complexity: O(N)
	*/
	std::string result(str.size(), ' ');

	size_t i = 0, right = str.size();

	while (i < str.size()) {
		auto space = str.find(' ', i);

		if (space != std::string::npos) {
			size_t len = space - i;
			size_t to_insert = right - len;

			for (size_t j = i; j < i + len; ) {
				result[to_insert] = str[j];

				++j;
				++to_insert;
			}

			right = right - len - 1;
			i = space + 1;
		} else {
			size_t len = str.size() - i;
			size_t to_insert = right - len;

			for (size_t k = i; k < str.size(); ) {
				result[to_insert] = str[k];

				++k;
				++to_insert;
			}

			i = str.size();
		}
	}

	return result;
}

int main() {
	std::string str;
	std::getline(std::cin >> std::ws, str);

	auto result = ConvertText(str);
	std::cout << result << '\n';
}