#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

void Solution(std::vector<size_t>& n_array, std::vector<size_t>& m_array, size_t n, size_t m) {
	/*
		Time Complexity: O(log(n + m))
		Memory Complexity: O(1)
	*/
	if (n > m) {
		std::swap(n_array, m_array);
		std::swap(n, m);
	}

	size_t left = 0, right = n, half = (n + m + 1) / 2;
	while (left <= right) {
		size_t n_middle = left + (right - left) / 2;
		size_t m_middle = half - n_middle;

		size_t n_left = (n_middle > 0) ? n_array[n_middle - 1] : 0;
		size_t n_right = (n_middle < n) ? n_array[n_middle] : SIZE_MAX;

		size_t m_left = (m_middle > 0) ? m_array[m_middle - 1] : 0;
		size_t m_right = (m_middle < m) ? m_array[m_middle] : SIZE_MAX;

		if (n_left <= m_right && m_left <= n_right) {
			if ((n + m) % 2 == 0) {
				std::cout << (std::max(n_left, m_left) + std::min(n_right, m_right)) / 2.0 << '\n';
			} else {
				std::cout << std::max(n_left, m_left) << '\n';
			}
			return;
		} else if (n_left > m_right) {
			right = n_middle - 1;
		} else if (m_left > n_right) {
			left = n_middle + 1;
		}
	}
}

int main() {
	size_t n, m;
	std::cin >> n >> m;

	std::vector<size_t> n_array(n), m_array(m);

	for (size_t i = 0; i < n; ++i) {
		std::cin >> n_array[i];
	}

	for (size_t i = 0; i < m; ++i) {
		std::cin >> m_array[i];
	}

	Solution(n_array, m_array, n, m);
}