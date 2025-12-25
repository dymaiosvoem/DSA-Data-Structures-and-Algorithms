/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются login, solved_tasks, fine. Храню все данные об участнике в структуре Participant.

	Строю кучу так: добавляю всех участников в массив и делаю Heapify(), чтобы установить свойство кучи с максимальным приоритетом.
	В Heapify() прохожу по индексам от (heap_.size() - 1) / 2 до 1, для каждого start делаю SiftDown(start).

	Приоритет участников определяется по 3 критериям:
		1) при сравнении двух участников выше будет идти тот, у которого решено больше задач;
		2) при равенстве числа решенных задач первым идет участник с меньшим штрафом;
		3) если же и штрафы совпадают, то первым будет тот, у которого логин идет раньше в алфавитном порядке.

	Следующий этап - сортировка, достаю лучшего участника из кучи и кладу его в sorted_heap, на его место в куче ставлю последнего
	участника и делаю просеивание вниз, чтобы сохранить свойство кучи с максимальным приоритетом. Делаю так до тех пор, пока
	heap_.size() > 1.

	На выходе получается отсортированный массив, вывожу login каждого участника.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: для любой вершины кучи приоритет не хуже приоритета детей.

	Методы:
		1) void push(const Participant& participant)
			-push добавляет участника в конец массива, инвариант кучи устанавливается после Heapify в методе sort().

		2) Participant pop_max()
			-достаю из кучи участника с максимальным приоритетом, на его место переношу самого последнего участника из кучи,
			удаляю последний элемент, так как перенес его в корень;
			-при просеивании вниз выбираю лучшего из детей и меняю местами, если корень хуже этого ребенка,
			тем самым восстанавливаю инвариант в текущей вершине;
			-когда обменивать нечего или дошел до листа, значит инвариант восстановлен.

		3) std::vector<Participant> sort()
			-перед сортировкой устанавливаю инвариант кучи методом Heapify();
			-повторяю pop_max() до тех пор, пока в куче есть участники.
			-каждый раз извлекаю лучшего, значит в sorted_heap попадают участники в порядке убывания приоритета.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть N - количество участников.

	Методы:
		push (за одну вставку):
			-вставка в конец кучи O(1).

		pop_max (за одно удаление):
			-перетащить участника с конца кучи в начало O(1);
			-удалить из конца O(1);
			-просеивание вниз O(log N).

		sort:
			-всего N раз выполняется pop_max();
			-вставка в конец отсортированного массива, участника с максимальным приоритетом O(1) - всего N раз, так как
			перекладываю каждого участника из кучи.

	Построение кучи Heapify: O(N).
	Удаление из кучи (N раз pop_max): O(N * log N).
	Перекладывание из кучи в отсортированный массив: O(N).

	Итог: O(N * log N).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	В каждом методе использую дополнительные переменные для выбора индексов: O(1).

	Только в методе sort() использую вспомогательную структуру (std::vector<Participant> sorted_heap), для хранения элементов
	кучи в отсортированном порядке:
		-heap_ хранит: O(N);
		-sorted_heap: O(N).

	Итог: O(N).
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Participant {
	Participant() = default;

	Participant(std::string login, int solved_tasks, int fine) :
		login_(login),
		solved_tasks_(solved_tasks),
		fine_(fine) {
	}

	std::string login_ = {};
	int solved_tasks_ = 0;
	int fine_ = 0;
};

class Heap {
public:
	explicit Heap(size_t size) {
		heap_.reserve(size + 1);
		heap_.push_back(Participant());
	}

	void push(const Participant& participant) {
		heap_.push_back(participant);
	}

	std::vector<Participant> sort() {
		if (heap_.size() <= 1) {
			return {};
		}

		Heapify();

		std::vector<Participant> sorted_heap;
		sorted_heap.reserve(heap_.size() - 1);

		while (heap_.size() > 1) {
			auto better_participant = pop_max();
			sorted_heap.push_back(better_participant);
		}

		return sorted_heap;
	}

private:
	std::vector<Participant> heap_;

	bool BetterParticipant(const Participant& a, const Participant& b) const {
		return std::make_tuple(-a.solved_tasks_, a.fine_, a.login_) <
			std::make_tuple(-b.solved_tasks_, b.fine_, b.login_);
	}

	void Heapify() {
		size_t start = (heap_.size() - 1) / 2;

		while (start > 0) {
			SiftDown(start);

			--start;
		}
	}

	void SiftDown(size_t index) {
		while (true) {
			size_t left = index * 2;
			size_t right = index * 2 + 1;

			if (left >= heap_.size()) {
				break;
			}

			size_t highest_priority = left;
			if (right < heap_.size() && BetterParticipant(heap_[right], heap_[left])) {
				highest_priority = right;
			}

			if (BetterParticipant(heap_[highest_priority], heap_[index])) {
				std::swap(heap_[highest_priority], heap_[index]);
				index = highest_priority;
			} else {
				break;
			}
		}
	}

	Participant pop_max() {
		assert(heap_.size() > 1);

		auto better_participant = heap_[1];
		heap_[1] = heap_[heap_.size() - 1];
		heap_.pop_back();
		SiftDown(1);

		return better_participant;
	}
};

void PrintResult(const std::vector<Participant>& result) {
	for (const auto& participant : result) {
		std::cout << participant.login_ << '\n';
	}
}

void Solution(size_t n) {
	Heap heap(n);

	size_t start = 0;
	while (start < n) {
		std::string login;
		int solved_task, fine;

		std::cin >> login >> solved_task >> fine;

		heap.push(Participant(login, solved_task, fine));

		++start;
	}

	auto result = heap.sort();
	PrintResult(result);
}

int main() {
	size_t n;
	std::cin >> n;

	Solution(n);
}