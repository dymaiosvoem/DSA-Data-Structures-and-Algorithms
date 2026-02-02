/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются очки, считаю сумму всех очков total. Если total нечетная, то разбить на две одинаковые части
	нельзя.

	Иначе ищу, можно ли набрать сумму half = total / 2; В dp_achievable считаю, какие суммы достижимы после обработки 
	первых i элементов массива points. Считаю что 0 достижим, dp_achievable[0] = true;

	Для каждого points[i] обновляю dp_achievable в обратном порядке перебирая j от half - points[i] до 0: если 
	dp_achievable[j] == true, то делаю next_sum = points[i] + j и ставлю dp_achievable[next_sum] = true; Предусматриваю 
	ранний выход: next_sum == half, то return true;

	Обратный проход нужен, чтобы каждый поинт не использовался несколько раз. В конце возвращаю dp_achievable[half];

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: dp_achievable[j] хранит булево, достижима ли сумма j, используя некоторое подмножество из первых i
	обработанных элементов массива points.

	Базовый случай: до обработки любых очков, достижимо только dp_achievable[0] == true, остальные false.

	Если сумма j была достижима до добавления points[i], то points[i] + j станет достижимой после. По j нужно проходить
	в обратном порядке, чтобы не использовать points[i] несколько раз при достижении новой суммы.

	Рассматриваю суммы только до j <= half - points[i], как только half достижима, возвращаю true.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть P = points.size(), H = half = total / 2 (dp_achievable.size()).

	Итог: O(P * H).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Хранение points из n очков: O(P);
	Хранение достижимых сумм (dp_achievable): O(H);

	Итог: O(P + H).
*/

#include <iostream>
#include <vector>

bool HasEqualSubsetPartition(const std::vector<int>& points, int total) {
	if (total % 2 != 0) {
		return false;
	}

	int half = total / 2;

	std::vector<bool> dp_achievable(half + 1, false);
	dp_achievable[0] = true;

	for (int i = 0; i < static_cast<int>(points.size()); ++i) {
		for (int j = half - points[i]; j >= 0; --j) {

			if (!dp_achievable[j]) {
				continue;
			}

			int next_sum = points[i] + j;

			if (next_sum == half) {
				return true;
			}

			dp_achievable[next_sum] = true;
		}
	}

	return dp_achievable[half];
}

int main() {
	size_t n;
	std::cin >> n;

	std::vector<int> points(n, 0);
	int total = 0;

	for (size_t i = 0; i < n; ++i) {
		std::cin >> points[i];

		total += points[i];
	}

	if (HasEqualSubsetPartition(points, total)) {
		std::cout << "True" << '\n';
	} else {
		std::cout << "False" << '\n';
	}
}