#include <algorithm>
#include <iostream>
#include <vector>

struct IdAndFreq {
	size_t id;
	size_t freq;
};

std::vector<size_t> MergeSort(const std::vector<size_t>& university_id_of_students) {
	if (university_id_of_students.size() <= 1) {
		return university_id_of_students;
	}

	size_t mid = university_id_of_students.size() / 2;

	std::vector<size_t> left(university_id_of_students.begin(), university_id_of_students.begin() + mid);
	left = MergeSort(left);

	std::vector<size_t> right(university_id_of_students.begin() + mid, university_id_of_students.end());
	right = MergeSort(right);

	std::vector<size_t> result(left.size() + right.size());

	size_t l = 0, r = 0, k = 0;
	while (l < left.size() && r < right.size()) {
		if (left[l] <= right[r]) {
			result[k] = left[l];
			++l;
		} else {
			result[k] = right[r];
			++r;
		}

		++k;
	}

	while (l < left.size()) {
		result[k] = left[l];
		++k;
		++l;
	}

	while (r < right.size()) {
		result[k] = right[r];
		++k;
		++r;
	}

	return result;
}

bool compare_freq_id(const IdAndFreq& left, const IdAndFreq& right) {
	return left.freq > right.freq || (left.freq == right.freq && left.id < right.id);
}

std::vector<IdAndFreq> MergeSortPairs(const std::vector<IdAndFreq>& freq_university_id_of_students) {
	if (freq_university_id_of_students.size() <= 1) {
		return freq_university_id_of_students;
	}

	size_t mid = freq_university_id_of_students.size() / 2;

	std::vector<IdAndFreq> left(freq_university_id_of_students.begin(), freq_university_id_of_students.begin() + mid);
	left = MergeSortPairs(left);

	std::vector<IdAndFreq> right(freq_university_id_of_students.begin() + mid, freq_university_id_of_students.end());
	right = MergeSortPairs(right);

	std::vector<IdAndFreq> result(left.size() + right.size());

	size_t l = 0, r = 0, k = 0;
	while (l < left.size() && r < right.size()) {
		if (compare_freq_id(left[l], right[r])) {
			result[k] = left[l];
			++l;
		} else {
			result[k] = right[r];
			++r;
		}

		++k;
	}

	while (l < left.size()) {
		result[k] = left[l];
		++k;
		++l;
	}

	while (r < right.size()) {
		result[k] = right[r];
		++k;
		++r;
	}

	return result;
}

void Solution(const std::vector<size_t>& university_id_of_students, size_t k) {
	/*
		Time Complexity: T(N * log N) + T(M * log M); N - MergeSort, M - MergeSortPairs
		Memory Complexity: O(N + M)
	*/
	std::vector<size_t> sorted_id = MergeSort(university_id_of_students);

	std::vector<IdAndFreq> freq_university_id_of_students;
	freq_university_id_of_students.reserve(sorted_id.size());

	size_t current_id = sorted_id[0];
	size_t freq = 1;

	for (size_t i = 1; i < sorted_id.size(); ++i) {
		if (sorted_id[i] == current_id) {
			++freq;
		} else {
			freq_university_id_of_students.push_back({ current_id, freq });
			current_id = sorted_id[i];
			freq = 1;
		}
	}

	freq_university_id_of_students.push_back({ current_id, freq });

	std::vector<IdAndFreq> sorted_freq = MergeSortPairs(freq_university_id_of_students);

	size_t end = std::min(sorted_freq.size(), k);

	for (size_t i = 0; i < end; ++i) {
		if (i) {
			std::cout << ' ';
		}
		std::cout << sorted_freq[i].id;
	}

	std::cout << '\n';
}

int main() {
	size_t count_students;
	std::cin >> count_students;

	std::vector<size_t> university_id_of_students(count_students);
	for (size_t i = 0; i < count_students; ++i) {
		std::cin >> university_id_of_students[i];
	}

	size_t k;
	std::cin >> k;

	Solution(university_id_of_students, k);
}