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
		hash_table_.resize(131'072);
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

	void put(int key, int value) {
		uint64_t bucket = HashKey(key);
		Node* head = hash_table_[bucket];

		Node* current = head;

		if (!current) {
			Node* new_node = new Node(key, value, nullptr);
			hash_table_[bucket] = new_node;
			return;
		}

		while (current != nullptr) {
			if (current->key_ == key) {
				current->value_ = value;
				return;
			}

			if (!current->next_) {
				Node* new_node = new Node(key, value, nullptr);
				current->next_ = new_node;
				return;
			}

			current = current->next_;
		}
	}

	std::optional<int> delete_key(int key) {
		uint64_t bucket = HashKey(key);
		Node* head = hash_table_[bucket];

		Node* prev = head;

		if (!prev->next_) {
			if (prev->key_ == key) {
				return prev->value_;
			} else {
				return std::nullopt;
			}
		}

		Node* next = prev->next_;

		while (next != nullptr) {
			if (prev->key_ == key) {
				int value = prev->value_;
			}
		}

		return std::nullopt;
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

void Solution(size_t count_request) {
	/*
		Time Complexity:
		Memory Complexity:
	*/
	HashTable hash_table;
	size_t start = 0;

	while (start < count_request) {
		std::string request;
		std::cin >> request;

		if (request == "get") {
			int key;
			std::cin >> key;

			if (hash_table.get(key).has_value()) {
				std::cout << hash_table.get(key).value() << '\n';
			} else {
				std::cout << "None" << '\n';
			}
		} else if (request == "put") {
			int key, value;
			std::cin >> key >> value;

			hash_table.put(key, value);
		} else {
			int key;
			std::cin >> key;

			if (hash_table.delete_key(key).has_value()) {
				std::cout << hash_table.delete_key(key).value() << '\n';
			} else {
				std::cout << "None" << '\n';
			}
		}

		++start;
	}
}

int main() {
	size_t count_request;
	std::cin >> count_request;

	Solution(count_request);
}