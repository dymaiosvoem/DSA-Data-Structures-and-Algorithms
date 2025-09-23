#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Stack {
public:
	explicit Stack(size_t size) {
		stack_.reserve(size);
	}

	void push(int num) {
		stack_.push_back(num);
	}

	int pop() {
		int num = top();
		stack_.pop_back();

		return num;
	}

	int top() const {
		return stack_.back();
	}

private:
	std::vector<int> stack_;
};

void Solution(std::string_view expression) {
	Stack stack(expression.size());

	size_t start = 0;
	size_t end = expression.size();

	while (start < end) {
		size_t space = expression.find(' ', start);

		if (space == std::string_view::npos) {
			space = end;
		}

		std::string_view expr = expression.substr(start, space - start);

		if (expr.size() == 1 && std::strchr("+-/*", expr[0])) {
			int right_num = stack.pop(), left_num = stack.pop();
			switch (expr[0]) {
			case '+':
				stack.push(left_num + right_num);
				break;
			case '-':
				stack.push(left_num - right_num);
				break;
			case '*':
				stack.push(left_num * right_num);
				break;
			case '/':
				int result = left_num / right_num;

				if (left_num % right_num != 0 && left_num < 0) {
					--result;
				}

				stack.push(result);
				break;
			}
		} else {
			stack.push(std::stoi(std::string(expr)));
		}

		start = (space < end) ? space + 1 : end;
	}

	std::cout << stack.top() << '\n';
}

int main() {
	std::string expression;
	std::getline(std::cin, expression);

	Solution(expression);
}