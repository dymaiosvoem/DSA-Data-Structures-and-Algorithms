#include <iostream>
#include <vector>

void Solution(int num) {
	if (num == 0) {
		std::cout << 0 << std::endl;
		return;
	}

	std::vector<int> binary_repres;

	while (num != 0) {
		int result = num % 2;
		binary_repres.push_back(result);
		num /= 2;
	}

	for (size_t i = binary_repres.size(); i > 0; ) {
		--i;
		std::cout << binary_repres[i];
	}
}

int main() {
	int number;
	std::cin >> number;

	Solution(number);
}