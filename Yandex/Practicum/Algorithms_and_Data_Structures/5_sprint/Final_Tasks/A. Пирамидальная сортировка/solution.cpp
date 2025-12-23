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

	std::string login_;
	int solved_tasks_;
	int fine_;
};

class Heap {
public:
	Heap(size_t size) {
		heap_.reserve(size + 1);
		heap_.push_back(Participant{});
	}

	void push(const Participant& participant) {
		heap_.push_back(participant);
		size_t index = heap_.size() - 1;
		SiftUp(index);
	}

	Participant pop_max() {
		assert(heap_.size() > 1);

		auto better_participant = heap_[1];
		heap_[1] = heap_[heap_.size() - 1];
		heap_.pop_back();
		SiftDown(1);

		return better_participant;
	}

	std::vector<Participant> sort() {
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

	bool BetterParticipant(const Participant& a, const Participant& b) const noexcept {
		return std::make_tuple(-a.solved_tasks_, a.fine_, a.login_) <
			std::make_tuple(-b.solved_tasks_, b.fine_, b.login_);
	}

	void SiftUp(size_t index) noexcept {
		if (index == 1) {
			return;
		}

		size_t parent_index = index / 2;

		if (BetterParticipant(heap_[index], heap_[parent_index])) {
			std::swap(heap_[index], heap_[parent_index]);
			SiftUp(parent_index);
		}
	}

	void SiftDown(size_t index) noexcept {
		size_t left = index * 2;
		size_t right = index * 2 + 1;

		if (left >= heap_.size()) {
			return;
		}

		size_t highset_priority = left;
		if (right < heap_.size() && BetterParticipant(heap_[right], heap_[left])) {
			highset_priority = right;
		}

		if (BetterParticipant(heap_[highset_priority], heap_[index])) {
			std::swap(heap_[highset_priority], heap_[index]);
			SiftDown(highset_priority);
		}
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