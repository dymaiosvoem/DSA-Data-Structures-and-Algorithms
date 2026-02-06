#include <iostream>
#include <string>

bool IsEvenAlphabetPosition(char ch) {
	return (static_cast<int>(ch) - static_cast<int>('a') + 1) % 2 == 0;
}

int CompareTwoStrings(const std::string& a, const std::string& b) {
	/*
		Time Complexity: O(|a| + |b|)
		Memory Complexity: O(1)
	*/
	size_t i = 0, j = 0;

	while (i < a.length() && j < b.length()) {
		if (IsEvenAlphabetPosition(a[i]) && IsEvenAlphabetPosition(b[j])) {
			if (a[i] != b[j]) {
				return a[i] < b[j] ? -1 : 1;
			}

			++i;
			++j;
		} else {
			if (!IsEvenAlphabetPosition(a[i])) {
				++i;
			}

			if (!IsEvenAlphabetPosition(b[j])) {
				++j;
			}
		}
	}

	if (i != a.length() || j != b.length()) {
		while (i < a.length()) {
			if (IsEvenAlphabetPosition(a[i])) {
				return 1;
			}

			++i;
		}

		while (j < b.length()) {
			if (IsEvenAlphabetPosition(b[j])) {
				return -1;
			}

			++j;
		}
	}

	return 0;
}

int main() {
	std::string a, b;
	std::cin >> a >> b;

	auto result = CompareTwoStrings(a, b);
	std::cout << result << '\n';
}