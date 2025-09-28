﻿/*
	-- ПРИНЦИП РАБОТЫ --
	Я реализовал двустороннюю очередь на основе динамического массива, заранее зарезервировав место
	под максимальный размер. Использовать список было бы не так эффективно, так как нужно хранить 2
	указателя (на ноду вперед и назад), что существенно увеличивает затраты по памяти, а также ухудшает
	кэш локальность (потому что ноды будут храниться в куче не непрерывном блоком памяти), доступ к
	элементам был бы дольше.

	Инвариантом является - кольцевой буфер. За начало и конец массива берем 0 индексы (где head_ указывает
	на самый первый элемент, а tail_ на следующий индекс от последнего элемента) и в зависимости от операции,
	обновляем индексы через взятие по модулю от max_size_, дабы не выйти за границы и не получить undefined behavior.

	Массив имеет в сумме 4 метода: 2 для реализации операций по вставке и 2 для удалений элементов.
	Крайние случаи учтены:
		-при удалении: если массив пустой (size_ == 0), то выведет ошибку операции.
		-при вставке: если размер массива равен ему максимальному размеру (size_ == max_size_), тоже выдаст ошибку.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Из принципа работы понятно, что при операции мы учитываем крайние случаи (0 <= size_ <= max_size_):
		-ошибки при удалении из пустой очереди.
		-ошибки при вставке в заполненную очередь.

	Сами операции двусторонней очереди корректно выполняют удаление и вставки, обновляя при этом
	правильно индексы. Сама двусторонняя очередь подразумевает возможность взаимодействовать с массивом
	с двух сторон, все это реализовано и работает без ошибок.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть количество команд - Q, тогда это будет то самое число, сколько раз мы должны будем взаимодествовать
	с массивом. Операции по вставкам и удалении проходят за No Amortize O(1), так как память заверзирована и используются
	операции [ ] для изменения массива.
	Итог: O(Q) + O(1) + O(1) + O(1) + O(1) = O(Q)

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Пусть размер массива - M, тогда затраты по памяти исходят от количества элементов хранящиеся в двусторонней
	очереди + вспомогательные счетчики для двусторонней очереди, где каждая - O(1).
	Итог: O(M) + O(1) + O(1) + O(1) + O(1) = O(M)
*/

#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Dequeue {
public:
	explicit Dequeue(size_t max_size_queue) : head_(0), tail_(0), size_(0), max_size_(max_size_queue) {
		dequeue_.resize(max_size_queue, 0);
	}

	bool push_back(int value) {
		if (max_size_ == size_) {
			return false;
		}

		dequeue_[tail_] = value;
		++size_;

		tail_ = (tail_ + 1) % max_size_;
		return true;
	}

	bool push_front(int value) {
		if (max_size_ == size_) {
			return false;
		}

		if (size_ == 0) {
			dequeue_[head_] = value;
			tail_ = (tail_ + 1) % max_size_;
		} else {
			head_ = (head_ + max_size_ - 1) % max_size_;
			dequeue_[head_] = value;
		}

		++size_;
		return true;
	}

	std::optional<int> pop_front() {
		if (size_ == 0) {
			return std::nullopt;
		}

		int remove_value = dequeue_[head_];
		std::cout << remove_value << '\n';

		dequeue_[head_] = NULL;
		head_ = (head_ + 1) % max_size_;
		--size_;

		return remove_value;
	}

	std::optional<int> pop_back() {
		if (size_ == 0) {
			return std::nullopt;
		}

		tail_ = (tail_ + max_size_ - 1) % max_size_;

		int remove_value = dequeue_[tail_];
		std::cout << remove_value << '\n';

		dequeue_[tail_] = NULL;
		--size_;
		return remove_value;
	}

private:
	std::vector<int> dequeue_;
	size_t head_;
	size_t tail_;
	size_t size_;
	size_t max_size_;
};

void Solution(size_t count_commands, size_t max_size_queue) {
	Dequeue dequeue(max_size_queue);
	size_t start = 0;

	while (start != count_commands) {
		std::string command;
		std::cin >> command;

		if (command == "push_back") {
			int num;
			std::cin >> num;

			if (!dequeue.push_back(num)) {
				std::cout << "error" << '\n';
			}
		} else if (command == "push_front") {
			int num;
			std::cin >> num;

			if (!dequeue.push_front(num)) {
				std::cout << "error" << '\n';
			}
		} else if (command == "pop_back") {
			if (!dequeue.pop_back().has_value()) {
				std::cout << "error" << '\n';
			}
		} else {
			if (!dequeue.pop_front().has_value()) {
				std::cout << "error" << '\n';
			}
		}

		++start;
	}
}

int main() {
	size_t count_commands, max_size_queue;
	std::cin >> count_commands >> max_size_queue;

	Solution(count_commands, max_size_queue);
}