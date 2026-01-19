#include <algorithm>
#include <iostream>
#include <vector>

struct Pile {
	explicit Pile(size_t cost_per_kg, size_t gold_kg)
		: cost_per_kg_(cost_per_kg),
		gold_kg_(gold_kg) {
	}

	size_t cost_per_kg_;
	size_t gold_kg_;
};

void SolveGoldFever(size_t backpack_capacity) {
	/*
		Time Complexity: O(N * log N), N - piles
		Memory Complexity: O(N)
	*/
	size_t pile_count;
	std::cin >> pile_count;

	std::vector<Pile> piles;
	piles.reserve(pile_count);

	for (size_t i = 0; i < pile_count; ++i) {
		size_t cost_per_kg, gold_kg;
		std::cin >> cost_per_kg >> gold_kg;

		piles.push_back(Pile(cost_per_kg, gold_kg));
	}

	std::sort(piles.begin(), piles.end(), [](const Pile& lhs, const Pile& rhs) {
		return (lhs.cost_per_kg_ > rhs.cost_per_kg_) || (lhs.cost_per_kg_ == rhs.cost_per_kg_ && lhs.gold_kg_ > rhs.gold_kg_);
		});

	size_t total_value = 0;

	for (size_t j = 0; j < piles.size(); ++j) {
		if (backpack_capacity > 0) {
			size_t can_take = std::min(backpack_capacity, piles[j].gold_kg_);

			backpack_capacity = backpack_capacity - can_take;
			total_value += can_take * piles[j].cost_per_kg_;
		} else {
			break;
		}
	}

	std::cout << total_value << '\n';
}

int main() {
	size_t backpack_capacity;
	std::cin >> backpack_capacity;

	SolveGoldFever(backpack_capacity);
}