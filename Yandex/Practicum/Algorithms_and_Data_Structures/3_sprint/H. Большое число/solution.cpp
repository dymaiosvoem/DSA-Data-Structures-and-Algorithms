#include <iostream>
#include <string>
#include <vector>

bool compare_keys(const std::string& current_num, const std::string& prev_num) {
	return current_num + prev_num > prev_num + current_num;
}

void Solution(std::vector<std::string>& nums, bool (*less)(const std::string&, const std::string&)) {
	/*
		Time Complexity: O(N^2)
		Memory Complexity: O(1)
	*/
	for (size_t i = 1; i < nums.size(); ++i) {
		std::string insert_num = nums[i];
		size_t j = i;

		while (j > 0 && less(insert_num, nums[j - 1])) {
			nums[j] = nums[j - 1];
			--j;
		}

		nums[j] = insert_num;
	}
}

int main() {
	size_t size;
	std::cin >> size;

	std::vector<std::string> nums(size, "");
	for (size_t start = 0; start < nums.size(); ++start) {
		std::cin >> nums[start];
	}

	Solution(nums, compare_keys);

	for (auto& n : nums) {
		std::cout << n;
	}
	std::cout << std::endl;
}