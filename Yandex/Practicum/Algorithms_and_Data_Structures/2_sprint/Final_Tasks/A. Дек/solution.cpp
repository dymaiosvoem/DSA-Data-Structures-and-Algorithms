#include <iostream>
#include <string>
#include <vector>

class Dequeue {
public:
	explicit Dequeue(size_t max_size_queue) : head_(0), tail_(0), size_(0), max_size_(max_size_queue) {
		dequeue_.resize(max_size_queue, 0);
	}

	void push_back(int value) {
		if (size_ == max_size_) {
			PrintMaxElementDequeueError();
			return;
		}

		dequeue_[tail_] = value;
		++size_;

		tail_ = (tail_ + 1) % max_size_;
	}

	void push_front(int value) {
		if (size_ == max_size_) {
			PrintMaxElementDequeueError();
			return;
		}

		if (size_ == 0) {
			dequeue_[head_] = value;
			tail_ = (tail_ + 1) % max_size_;
		} else {
			head_ = (head_ + max_size_ - 1) % max_size_;
			dequeue_[head_] = value;
		}

		++size_;
	}

	void pop_front() {
		if (size_ == 0) {
			PrintEmptyDequeueError();
			return;
		}

		std::cout << dequeue_[head_] << '\n';

		dequeue_[head_] = NULL;
		head_ = (head_ + 1) % max_size_;
		--size_;
	}

	void pop_back() {
		if (size_ == 0) {
			PrintEmptyDequeueError();
			return;
		}

		tail_ = (tail_ + max_size_ - 1) % max_size_;

		std::cout << dequeue_[tail_] << '\n';

		dequeue_[tail_] = NULL;
		--size_;
	}

private:
	std::vector<int> dequeue_;
	size_t head_;
	size_t tail_;
	size_t size_;
	size_t max_size_;

	static void PrintMaxElementDequeueError() {
		std::cout << "error" << '\n';
	}

	static void PrintEmptyDequeueError() {
		std::cout << "error" << '\n';
	}
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

			dequeue.push_back(num);
		} else if (command == "push_front") {
			int num;
			std::cin >> num;

			dequeue.push_front(num);
		} else if (command == "pop_back") {
			dequeue.pop_back();
		} else {
			dequeue.pop_front();
		}

		++start;
	}
}

int main() {
	size_t count_commands, max_size_queue;
	std::cin >> count_commands >> max_size_queue;

	Solution(count_commands, max_size_queue);
}