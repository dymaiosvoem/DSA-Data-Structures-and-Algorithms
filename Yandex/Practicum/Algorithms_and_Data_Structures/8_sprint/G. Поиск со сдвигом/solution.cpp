#include <iostream>
#include <vector>

int FindPatternOccurrence(const std::vector<int>& X_temperature, const std::vector<int>& A_temperature, int start) {
	if (X_temperature.size() < A_temperature.size()) {
		return -1;
	}

	for (int pos = start; pos <= static_cast<int>(X_temperature.size() - A_temperature.size()); ++pos) {

		int c = A_temperature[0] - X_temperature[pos];
		bool match = true;

		for (int offset = 0; offset < static_cast<int>(A_temperature.size()); ++offset) {
			if (X_temperature[pos + offset] + c != A_temperature[offset]) {
				match = false;

				break;
			}
		}

		if (match) {
			return pos;
		}
	}

	return -1;
}

std::vector<int> FindAllPatternOccurrence(const std::vector<int>& X_temperature, const std::vector<int>& A_temperature) {
	/*
		X - X_temperature, A - A_temperature, P - occurences.size()
		Time Complexity: O(|X| * |A|)
		Memory Complexity: O(P), P = |X| - |A| + 1
	*/
	std::vector<int> occurrences;
	occurrences.reserve(X_temperature.size() - A_temperature.size() + 1);

	int start = 1;
	int pos;

	while ((pos = FindPatternOccurrence(X_temperature, A_temperature, start)) != -1) {
		occurrences.push_back(pos);
		start = pos + 1;
	}

	return occurrences;
}

void PrintOccurrences(const std::vector<int>& occurrences) {
	for (size_t i = 0; i < occurrences.size(); ++i) {
		if (i) {
			std::cout << ' ' << occurrences[i];
		} else {
			std::cout << occurrences[i];
		}
	}

	std::cout << '\n';
}

int main() {
	size_t n;
	std::cin >> n;

	std::vector<int> X_temperature(n + 1, 0);
	for (size_t i = 1; i < X_temperature.size(); ++i) {
		std::cin >> X_temperature[i];
	}

	size_t m;
	std::cin >> m;

	std::vector<int> A_temperature(m, 0);
	for (size_t j = 0; j < A_temperature.size(); ++j) {
		std::cin >> A_temperature[j];
	}

	auto occurrences = FindAllPatternOccurrence(X_temperature, A_temperature);
	PrintOccurrences(occurrences);
}