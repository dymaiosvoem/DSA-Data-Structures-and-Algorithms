/*
	-- ПРИНЦИП РАБОТЫ --
    Используется хеш-таблица с разрешением коллизий методом цепочек.
	Хеш-функция реализована метод умножения:
		uint64_t hash = static_cast<uint64_t>(key);
		uint64_t bucket = (hash * KNUTH_64) >> (64 - p_).
	Здесь p_ = 17, поэтому размер таблицы равен 2^17 корзин.

	Работа методов класса:
		-put(key, value): 
		    1) вычисляю индекс корзины bucket по key (через хеш-функцию);
			2) если корзина пуста hash_table_[bucket] == nullptr: 
				-создаю новый узел Node(key, value, nullptr)
				-записываю указатель в hash_table_[bucket] и делаю return;
			3) если в корзине есть цепочка:
				-если встречаю узел с тем же key (head->key_ == key), обновляю значение (head->value_ = value) и возвращаюсь;
				-если дошел до конца (!head->next_), добавляю новый узел в хвост, после выхожу из метода.

		-get(key): 
			1) вычисляю индекс корзины bucket по key (через хеш-функцию);
			2) беру указатель head = hash_table_[bucket] и иду по цепочке, пока head != nullptr:
				-если встречаю узел с тем же key (head->key_ == key), то возвращаю head->value_;
				-иначе сдвигаю указатель head = head->next_ и продолжаю обход.
			3) если дошел до конца цепочки и нужный ключ не найден, то return std::nullopt.

		-delete_key(key): 
			1) вычисляю индекс корзины bucket по key (через хеш-функцию);
			2) беру указатель prev = hash_table_[bucket] на голову цепочки:
				-если корзина пуста !prev:
				-возвращаю return std::nullopt.
			3) завожу указатель next = prev->next_, если первый узел цепочки содержит нужный нам key (prev->key_ == key):
				-сохраняю значение (value = prev->value_);
				-сдвигаю голову цепочки (hash_table_[bucket] = next);
				-удаляю старый узел (delete prev) и возвращаю значение (return value).
			4) иначе просматриваю оставшуюся часть цепочки, пока (next != nullptr):
				-если next->key_ == key, то сохраняю значение (value = next->value_);
				-вырезаю узел из списка (prev->next_ = next->next_)
				-удаляю узел из списка (delete next) и возвращаю значение (return value);
				-иначе сдвигаю указатели prev = next и next = next->next_.

			5) если дошел до конца цепоки и не встретил нужный key, то возвращаю return std::nullopt.

    -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант решения:
		1) для каждого key, существует не более одного узла в хеш-таблице;
		2) узел с key всегда находится в цепочке корзины с индексом bucket = HashKey(key).

	Корректность put(key, value):
		1) индекс корзины вычисляется из key с помощью HashKey(key;
		2) просматривается цепочка только этой корзины:
			-если в цепочке есть узел с тем же key, то обновляю его значение;
			-если узла нет с тем же ключом, добавляем новый узел в цепочку.

	Корректность get(key):
		1) индекс корзины вычисляется из key с помощью HashKey(key);
		2) если узел с ключом key существует, он обязан находиться в цепочке именно этой корзины. делаю обход по всей цепочке:
			-если в цепочке есть узел с тем же key, то достаю его значение;
			-если узла нет с тем же ключом, возвращаю std::nullopt.

	Корректность delete_key(key):
		1) Индекс корзины вычисляется из key с помощью HashKey(key):
			-если корзина пуста, возвращаю std::nullopt;
			-если первый узел цепочки содержит нужный key, то сдвигаю голову цепочки на следующий узел и удаляю старый, 
			остальные узлы не трогаю;
			-при обходе остальной части цепочки, либо нахожу ключ и также перезаписываю указатели и удаляю нужный, либо дохожу до конца
			и ничего не делаю.
		2) после delete_key либо единственный узел с данным key удаляется, либо таблица остается в прежнем состоянии

    -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть N - количество ключей, M - количество корзин в хеш таблице.
	Тогда load fator(a) = N / M = 10^5 / 2^17 = 0.76.

	Для каждой операции put / get / delete_key:
		-вычисление хеша ключа и номер корзины проходят за O(1);
		-обход цепочки длины L занимает O(L);
		-в равномерном распределении ключей, средняя длина цепочки L = O(a), поэтому операции будут работать за O(1) + O(a).

	В худшем случае, когда все ключи попали в одну корзину, тогда обход цепочки будет выполняться за O(N), но при выбранной хеш-функции
	и load factor - маловероятно.

    Итог: Averege: O(1) + O(a) = O(1 + a)
		  Worse: O(N)

    -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Пусть N - количество ключей, M - количество корзин в хеш таблице.

	Хранится:
		-массив из M указателей на головы цепочек;
		-до N узлов в одной корзине.

    Итог: O(N) + O(M) = O(N + M)
*/

#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

inline constexpr uint64_t KNUTH_64 = 11400714819323198485ull;

struct Node {
	Node(int key, int value, Node* next) : key_(key), value_(value), next_(next) {
	}

	int key_;
	int value_;
	Node* next_ = nullptr;
};

class HashTable {
public:
	HashTable() : p_(17) {
		hash_table_.resize(1ull << p_, nullptr);
	}

	void put(int key, int value) {
		uint64_t bucket = HashKey(key);
		Node* head = hash_table_[bucket];

		if (!head) {
			hash_table_[bucket] = new Node(key, value, nullptr);
			return;
		}

		while (head != nullptr) {
			if (head->key_ == key) {
				head->value_ = value;
				return;
			}

			if (!head->next_) {
				head->next_ = new Node(key, value, nullptr);
				return;
			}

			head = head->next_;
		}
	}

	std::optional<int> get(int key) const {
		uint64_t bucket = HashKey(key);
		Node* head = hash_table_[bucket];

		while (head != nullptr) {
			if (head->key_ == key) {
				return head->value_;
			}

			head = head->next_;
		}

		return std::nullopt;
	}

	std::optional<int> delete_key(int key) {
		uint64_t bucket = HashKey(key);
		Node* prev = hash_table_[bucket];

		if (!prev) {
			return std::nullopt;
		}

		Node* next = prev->next_;

		if (prev->key_ == key) {
			int value = prev->value_;
			hash_table_[bucket] = next;

			delete prev;
			return value;
		}

		while (next != nullptr) {
			if (next->key_ == key) {
				int value = next->value_;
				prev->next_ = next->next_;

				delete next;
				return value;
			}

			prev = next;
			next = next->next_;
		}

		return std::nullopt;
	}

	~HashTable() {
		for (size_t i = 0; i < hash_table_.size(); ++i) {
			if (!hash_table_[i]) {
				continue;
			} else {
				Node* head = hash_table_[i];

				while (head != nullptr) {
					Node* next = head->next_;
					delete head;
					head = next;
				}
			}
		}
	}

private:
	std::vector<Node*> hash_table_;
	size_t p_;

	uint64_t HashKey(int key) const noexcept {
		uint64_t hash = static_cast<uint64_t>(key);
		uint64_t bucket = (hash * KNUTH_64) >> (64 - p_);

		return bucket;
	}
};

void PrintOptional(const std::optional<int>& result) {
	if (result.has_value()) {
		std::cout << result.value() << '\n';
	} else {
		std::cout << "None" << '\n';
	}
}

void Solution(size_t count_request) {
	HashTable hash_table;
	size_t start = 0;

	while (start < count_request) {
		std::string request;
		std::cin >> request;

		if (request == "get") {
			int key;
			std::cin >> key;

			PrintOptional(hash_table.get(key));
		} else if (request == "put") {
			int key, value;
			std::cin >> key >> value;

			hash_table.put(key, value);
		} else if (request == "delete") {
			int key;
			std::cin >> key;

			PrintOptional(hash_table.delete_key(key));
		}

		++start;
	}
}

int main() {
	size_t count_request;
	std::cin >> count_request;

	Solution(count_request);
}