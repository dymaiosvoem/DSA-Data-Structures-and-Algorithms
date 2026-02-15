/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются n запакованных строк. Сохраняю первую распакованную строку и считаю ее целиком общим префиксом. 
	Считываю и распаковываю остальные строки поочередно и сравниваю с текущим префиксом (сравнение идет слева 
	направо пока символы общего префикса и новой распакованной строки равны), обновляю общий префикс до длины 
	совпавшей части.

	В конце вывожу полученный общий префикс для всех распакованных строк.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: после обработки k строк, где k >= 1, строка common_prefix равна наибольшему общему префиксу k строк.

	База: k = 1, после распаковки первой строки, наибольший общий префикс для одной строки равен ей самой.

	Переход: при шаге k + 1 распаковываю новую строку и посимвольно сравниваю с текущим common_prefix слева направо,
	пока символы совпадают. длина совпавшая части, становится новым общим префиксом для всех распакованных строк k + 1.

	После обработки всех n строк следует, что common_prefix равен наибольшему общему префиксу n распакованных строк.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	S = packed_str.length(), P = length decoded string.

	DecodePackedString(packed_str): 
		1) проход по всем символам - O(S);
		2) все операции append суммарно добавлют столько символов, сколько оказалось в распакованной строке - O(P).
		
		Итог для распаковки одной строки - O(S + P).

	В Solution(n) для каждой строки выполняю распаковку O(S_i + P_i) и сравнение с текущим префиксом 
	O(min(|common_prefix|, P_i)), в худшем случае O(P_i).

	Итог: O(sum(S_i + P_i)).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	M = max length decoded string, C = common_prefix.length().

	На каждом шаге храню:
		1) Текущую распакованную строку (decoded_str) - O(M);
		2) Текущий общий префикс (common_prefix) - O(C);

	В DecodePackedString(..) использую стек, в худшем случае занимает памяти O(M).

	Так как M >= C, то O(M).

	Итог: O(M).
*/

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

		if (common_prefix.empty()) {
			break;
		}
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