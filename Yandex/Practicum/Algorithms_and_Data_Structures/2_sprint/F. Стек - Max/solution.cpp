#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class StackMax {
public:
	explicit StackMax(size_t size) {
		stack_.reserve(size);
		max_nums_.reserve(size);
	}

	void push(int x) {
		stack_.push_back(x);

		if (max_nums_.empty()) {
			max_nums_.push_back(x);
			return;
		}

		max_nums_.push_back(std::max(max_nums_.back(), x));
	}

	void pop() {
		if (IsEmpty()) {
			std::cout << "error" << '\n';
			return;
		}

		stack_.pop_back();
		max_nums_.pop_back();
	}

	void get_max() const {
		if (IsEmpty()) {
			std::cout << "None" << '\n';
			return;
		}

		std::cout << max_nums_.back() << '\n';
	}

private:
	std::vector<int> stack_;
	std::vector<int> max_nums_;

	bool IsEmpty() const {
		return stack_.empty();
	}
};

void Solution(size_t size) {
	/*
		Time Complexity: O(N)
		Memory Complexity: O(N)
	*/
	StackMax stack(size);
	size_t start = 0;

	while (start < size) {
		std::string command;
		std::getline(std::cin >> std::ws, command);

		if (command == "get_max") {
			stack.get_max();
		} else if (command == "pop") {
			stack.pop();
		} else {
			size_t space = command.find(' ');
			int num = std::stoi(command.substr(space + 1));

			stack.push(num);
		}

		++start;
	}
}

int main() {
	size_t count_commands;
	std::cin >> count_commands;

	Solution(count_commands);
}