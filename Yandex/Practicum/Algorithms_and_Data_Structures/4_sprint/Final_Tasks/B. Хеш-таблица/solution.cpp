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
	/*
		a = N / M = 10^5 / 2^17 = 0.76 (N - count_keys; M - count_buckets)
		Time Complexity: get/put/delete_key working for: O(1) for hash + O(a) for chain = O(1 + a)
		Memory Complexity: O(N + M)
	*/
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