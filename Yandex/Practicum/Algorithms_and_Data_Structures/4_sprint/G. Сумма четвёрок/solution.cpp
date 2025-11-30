#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>

/*
6
0
1 0 -1 0 2 -2

result:

N(N - 1) / 2 = (N^2 - N) / 2 = 6 * 5 / 2 = 15 пар

sort: -2 -1 0 0 1 2
idx and sum:
(-2, -1) = -3
(-2, 0) = -2
(-2, 0) = -2
(-2, 1) = -1
(-2, 2) = 0
(-1, 0) = -1
(-1, 0) = -1
(-1, 1) = 0
(-1, 2) = 1
(0, 0) = 0
(0, 1) = 1
(0, 2) = 2
(0, 1) = 1
(0, 2) = 2
(1, 2) = 3

result: -2 -1 1 2
		-2  0 0 2
		-1  0 0 1
*/

struct SumAndIndexes {
	SumAndIndexes(long long sum, size_t i, size_t j) : sum_(sum), i_(i), j_(j) {
	}

	long long sum_;
	size_t i_;
	size_t j_;
};

struct IndexesFours {
	IndexesFours(size_t i, size_t j, size_t k, size_t l) : i_(i), j_(j), k_(k), l_(l) {
	}

	size_t i_;
	size_t j_;
	size_t k_;
	size_t l_;
};

void Solution(std::vector<long long>& elements, long long S) {
	std::sort(elements.begin(), elements.end());

	size_t N = elements.size();

	if (N < 4) {
		return;
	}

	size_t count_pairs = (N * (N - 1)) / 2;

	std::vector<SumAndIndexes> sum_idxes;
	sum_idxes.reserve(count_pairs);

	for (size_t i = 0; i < elements.size(); ++i) {
		for (size_t j = i + 1; j < elements.size(); ++j) {
			long long sum = elements[i] + elements[j];

			sum_idxes.emplace_back(SumAndIndexes(sum, i, j));
		}
	}

	std::sort(sum_idxes.begin(), sum_idxes.end(), [](const SumAndIndexes& lhs, const SumAndIndexes& rhs) {
		return lhs.sum_ < rhs.sum_;
		});

	std::set<IndexesFours> uniq_fours_idxes;
	size_t L = 0, R = sum_idxes.size() - 1;

	while (L < R) {
		long long sum_L = sum_idxes[L].sum_;
		long long sum_R = sum_idxes[R].sum_;
		long long total = sum_L + sum_R;

		if (total < S) {
			++L;
		} else if (total > S) {
			--R;
		} else if (total == S) {
			uniq_fours_idxes.insert(IndexesFours(sum_idxes[L].i_, sum_idxes[L].j_, sum_idxes[R].i_, sum_idxes[R].j_));
		}
	}

	for (const auto& [i, j, k, l] : uniq_fours_idxes) {
		std::cout << elements[i] << ' ' << elements[j] << ' ' << elements[k] << ' ' << elements[l] << '\n';
	}
}

int main() {
	size_t count_elem;
	std::cin >> count_elem;

	long long S;
	std::cin >> S;

	std::vector<long long> elements(count_elem);
	for (size_t i = 0; i < count_elem; ++i) {
		std::cin >> elements[i];
	}

	Solution(elements, S);
}