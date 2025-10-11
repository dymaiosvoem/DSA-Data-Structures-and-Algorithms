#include <vector>
#include <cassert>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

std::vector<int> merge(
	CIterator left_begin, CIterator left_end,
	CIterator right_begin, CIterator right_end) {

	size_t left_size = left_end - left_begin;
	size_t right_size = right_end - right_begin;

	std::vector<int> result(left_size + right_size, 0);
	size_t idx_to_insert = 0;

	while (left_begin != left_end && right_begin != right_end) {
		if (*left_begin <= *right_begin) {
			result[idx_to_insert] = *left_begin;

			++idx_to_insert;
			++left_begin;
		} else {
			result[idx_to_insert] = *right_begin;

			++idx_to_insert;
			++right_begin;
		}
	}

	while (left_begin != left_end) {
		result[idx_to_insert] = *left_begin;

		++idx_to_insert;
		++left_begin;
	}

	while (right_begin != right_end) {
		result[idx_to_insert] = *right_begin;

		++idx_to_insert;
		++right_begin;
	}

	return result;
}

void merge_sort(Iterator begin, Iterator end) {
	/*
		Time Complexity: T(N * log N)
		Memory Complexity: O(N)
	*/
	size_t size = end - begin;

	if (size == 1) {
		return;
	}

	Iterator mid = begin + size / 2;

	std::vector<int> left(begin, mid);
	merge_sort(left.begin(), left.end());

	std::vector<int> right(mid, end);
	merge_sort(right.begin(), right.end());

	std::vector<int> result = merge(left.begin(), left.end(), right.begin(), right.end());

	std::copy(result.begin(), result.end(), begin);
}

void test_merge_sort() {
	std::vector<int> a = { 1, 4, 9 };
	std::vector<int> b = { 2, 10, 11 };
	std::vector<int> c = merge(a.cbegin(), a.cend(), b.cbegin(), b.cend());
	std::vector<int> expected = { 1, 2, 4, 9, 10, 11 };
	assert(c == expected);
	std::vector<int> d = { 1, 4, 2, 10, 1, 2 };
	std::vector<int> sorted = { 1, 1, 2, 2, 4, 10 };
	merge_sort(d.begin(), d.end());
	assert(d == sorted);
}