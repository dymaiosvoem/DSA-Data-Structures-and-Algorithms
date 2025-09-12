#include <iostream>
#include <string>

void Solution(const std::string& num1, const std::string& num2) {
	/*
		Time Complexity: O(N), where N is the length of place values of the largest number
		Memory Complexity: O(N), where N is the length of place values of the largest number
	*/
	size_t size_num = num1.size();
	std::string result(size_num + 1, '0');

	int carry = 0;

	for (size_t begin = size_num; begin > 0; ) {
		--begin;
		int sum = (num1[begin] - '0') + (num2[begin] - '0') + carry;

		if (sum == 0) {
			result[begin + 1] = '0';
			carry = 0;
		} else if (sum == 1) {
			result[begin + 1] = '1';
			carry = 0;
		} else if (sum == 2) {
			result[begin + 1] = '0';
			carry = 1;
		} else {
			result[begin + 1] = '1';
			carry = 1;
		}
	}

	if (carry == 1) {
		result[0] = '1';
		std::cout << result << std::endl;
	} else {
		std::cout << result.substr(1) << std::endl;
	}
}

int main() {
	std::string first_num, second_num;
	std::cin >> first_num >> second_num;

	const int delta = std::abs(static_cast<int>(first_num.length() - second_num.length()));

	if (first_num.length() < second_num.length()) {
		first_num = std::string(delta, '0') + first_num;
	} else if (first_num.length() > second_num.length()) {
		second_num = std::string(delta, '0') + second_num;
	}

	Solution(first_num, second_num);
}