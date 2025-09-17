#include <iostream>
#include <string>

struct Node {
	explicit Node(int val) : value_(val) {}

	Node* next_ = nullptr;
	int value_;
};

class QueueList {
public:
	QueueList() : head_(nullptr), tail_(nullptr), size_(0) {}
	QueueList(const QueueList&) = delete;
	QueueList& operator=(const QueueList&) = delete;

	void get() {
		if (!head_) {
			PrintEmptyQueueError();
			return;
		}

		std::cout << head_->value_ << '\n';

		DeleteHeadNode();
		--size_;
	}

	void put(int x) {
		if (!head_) {
			head_ = tail_ = new Node(x);
			++size_;
			return;
		}

		tail_->next_ = new Node(x);
		tail_ = tail_->next_;
		++size_;
	}

	void size() const noexcept {
		std::cout << size_ << '\n';
	}

	~QueueList() {
		while (head_) {
			DeleteHeadNode();
		}
	}

private:
	Node* head_;
	Node* tail_;
	size_t size_;

	static void PrintEmptyQueueError() {
		std::cout << "error" << '\n';
	}

	void DeleteHeadNode() noexcept {
		Node* node = head_;
		head_ = head_->next_;

		delete node;

		if (!head_) {
			tail_ = nullptr;
		}
	}
};

void Solution(size_t end) {
	/*
		Time Complexity: O(N) N = count commands and O(1) for each operation
		Memory Complexity: O(N) N = count of nodes
	*/
	QueueList queue;
	size_t start = 0;

	while (start != end) {
		std::string command;
		std::cin >> command;

		if (command == "get") {
			queue.get();
		} else if (command == "size") {
			queue.size();
		} else {
			int num;
			std::cin >> num;

			queue.put(num);
		}

		++start;
	}
}

int main() {
	size_t count_commands;
	std::cin >> count_commands;

	Solution(count_commands);
}