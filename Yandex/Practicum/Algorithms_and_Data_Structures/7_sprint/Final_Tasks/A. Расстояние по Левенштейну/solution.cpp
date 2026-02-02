/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются 2 строки s и t. Храню 2 строки dp: prev и curr, где prev[j] это расстояние для первых i - 1 символов s
	и первых j символов t. curr[j] расстояние для первых i символов s и первых j символов t.

	Далее считаю расстояния:
		-если s[i - 1] == t[j - 1], то curr[j] = prev[j - 1];
		-иначе выбираю из 3 вариантов самый минимальный: prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + 1;
		-после заполнения строки делаю swap(prev, curr).

	В конце возвращаю prev[t_size] и печатаю расстояние.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант внешнего цикла по i: перед началом обработки очередного i массив prev[j] содержит минимальное число
	операций, чтобы первые i - 1 символов s превратить в первые j символов t.

	Инвариант внутреннего цикла по j: после вычисления curr[j] он содержит минимальное число операций, чтобы первые
	i символов s превратить в первые j символов t.

	Базовые случаи:
		-prev[j] = j при i = 0: из пустой строки получить первые j символов t можно только вставками;
		-curr[0] = i для каждого i: превратить первые i символов s в пустую строку можно только удалениями;

	Для j ≥ 1:
		-если s[i - 1] == t[j - 1], то curr[j] = prev[j - 1] (последние символы совпали, операция не нужна);
		-иначе минимум из трех вариантов:
			1) удалить: prev[j] + 1;
			2) вставить: curr[j - 1] + 1;
			3) заменить: prev[j - 1] + 1.

	После вычисления всей строки curr делаю swap(prev, curr). После обработки всех i ответ лежит в prev[t_size].

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть S = s.size(), T = t.size().

	Инициализация prev: O(T);
	Проход по всем символам из s: O(S * T), где берется min от 3 значений O(1).

	Итог: O(S * T).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Хранение prev: O(T);
	Хранение curr: O(T).

	Итог: O(T).
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

size_t ComputeLevenshteinDistance(const std::string& s, const std::string& t) {
	size_t s_size = s.size(), t_size = t.size();

	std::vector<size_t> prev(t_size + 1, 0), curr(t_size + 1, 0);

	std::iota(prev.begin(), prev.end(), 0);

	for (size_t i = 1; i <= s_size; ++i) {
		for (size_t j = 0; j <= t_size; ++j) {
			if (j == 0) {
				curr[j] = i;

				continue;
			}

			if (s[i - 1] == t[j - 1]) {
				curr[j] = prev[j - 1];
			} else {
				curr[j] = std::min({ prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + 1 });
			}
		}

		prev.swap(curr);
	}

	return prev[t_size];
}

int main() {
	std::string s, t;
	std::cin >> s >> t;

	auto distance = ComputeLevenshteinDistance(s, t);
	std::cout << distance << '\n';
}