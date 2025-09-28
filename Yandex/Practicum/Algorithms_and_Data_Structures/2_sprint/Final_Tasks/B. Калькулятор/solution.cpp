/*
	-- ПРИНЦИП РАБОТЫ --
	За основу взял АТД стек, на динамическом массиве, заранее зарезервировав место под максимальный размер
	выражения, поэтому стек никогда не будет переполнен и не будет перевыделять память, так как я не учитываю пробелы
	и сами операции, а лишь натуральные числа.

	На вход у нас подается выражение и мы его парсим, добавляя при этом все натуральные числа в стек до тех пор,
	пока не встретим знак операции над ними. Стек работает по принципу LIFO, поэтому когда попадается знак операции (он
	требует наличие >= 2 операндов), то достаем последнее натуральное число (методом pop(), где используется метод top(),
	для захвата верхнего значения) и обозначаем его как правый операнд (сохраняя его для операции, pop() возвращает натуральное число),
	следом берем следующий элемент на верху стека (по той же схеме, как и справым операндом; сохраняем его как левый операнд), далее
	выполняем операцию, которая нам попалась над двумя операндами и кладем результат обратно на вершину стека. И так повторяем,
	пока не закончатся встречаться знаки операции.

	Краевые случаи:
		-когда числитель по модулю от знаменателя != 0 и числитель отрицательное число, то результат убавляем на единицу, чтобы
		округление работало правильно.
		-когда встречается операция '-' и отрицательное натуральное число '-1', это парсится захватом string_view, если
		string_view size == 1, то парсится как операция, если size >= 2, то как операнд.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Из принципа работы понятно, что при каждом встречающемся знаке операции, всегда выполняется над двумя операндами через метод
	pop() и кладется обратно в стек методом push_back(). Чтобы когда закончатся знаки операций, можно достать результат из вершины стека методом top().

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть количество всех токенов - S. Проходясь по каждому токену мы используем методы, которые работают за No Amortize O(1).
	Итог: O(S) + O(1) + O(1) + O(1) = O(S);

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Пусть количество токенов (только операнды) - T. Учитываем максимальное значение T. 
	Итог: O(T);
*/

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