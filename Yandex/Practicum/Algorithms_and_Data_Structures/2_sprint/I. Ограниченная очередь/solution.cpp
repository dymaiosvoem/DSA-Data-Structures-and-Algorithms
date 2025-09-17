#include <iostream>
#include <vector>

class MyQueueSized {
public:
	explicit MyQueueSized(size_t max_size)
		: queue_(max_size), head_(0), tail_(0), max_n_(max_size), size_(0) {
	}

	void push(int num) {
		if (size_ == max_n_) {
			PrintMaxSizeQueueError();
			return;
		}

		queue_[tail_] = num;
		tail_ = (tail_ + 1) % max_n_;
		++size_;
	}

	void pop() {
		if (GetSize() == 0) {
			PrintEmptyQueueError();
			return;
		}

		PrintFirstElemQueue();

		queue_[head_] = NULL;
		head_ = (head_ + 1) % max_n_;
		--size_;
	}

	void peek() const {
		if (GetSize() == 0) {
			PrintEmptyQueueError();
			return;
		}

		PrintFirstElemQueue();
	}

	void size() const {
		std::cout << GetSize() << '\n';
	}

private:
	std::vector<int> queue_;
	size_t head_;
	size_t tail_;
	size_t max_n_;
	size_t size_;

	size_t GetSize() const noexcept {
		return size_;
	}

	static void PrintMaxSizeQueueError() {
		std::cout << "error" << '\n';
	}

	static void PrintEmptyQueueError() {
		std::cout << "None" << '\n';
	}

	void PrintFirstElemQueue() const {
		std::cout << queue_[head_] << '\n';
	}
};

void Solution(size_t end, size_t max_size) {
	/*
		Time Complexity: O(N) N = count commands and O(1) for each operation
		Memory Complexity: O(M) M = max_size
	*/

	MyQueueSized queue(max_size);
	size_t start = 0;

	while (start != end) {
		std::string command;
		std::cin >> command;

		if (command == "size") {
			queue.size();
		} else if (command == "pop") {
			queue.pop();
		} else if (command == "peek") {
			queue.peek();
		} else {
			int num;
			std::cin >> num;

			queue.push(num);
		}

		++start;
	}
}

int main() {
	size_t count_commands, max_size_queue;
	std::cin >> count_commands >> max_size_queue;

	Solution(count_commands, max_size_queue);
}