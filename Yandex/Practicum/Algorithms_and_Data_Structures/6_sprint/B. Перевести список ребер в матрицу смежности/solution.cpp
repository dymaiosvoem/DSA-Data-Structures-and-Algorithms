#include <cstdint>
#include <iostream>
#include <vector>

void PrintAdjacencyMatrix(const std::vector<std::vector<std::uint8_t>>& adjacency_mtrx) {
	for (size_t vertex = 0; vertex < adjacency_mtrx.size(); ++vertex) {
		for (size_t idx = 0; idx < adjacency_mtrx[vertex].size(); ++idx) {
			if (idx) {
				std::cout << ' ' << static_cast<int>(adjacency_mtrx[vertex][idx]);
			} else {
				std::cout << static_cast<int>(adjacency_mtrx[vertex][idx]);
			}
		}

		std::cout << '\n';
	}
}

void Solution(size_t n, size_t m) {
	/*
		Time Complexity: O(m + n^2)
		Memory Complexity: O(n^2)
	*/
	std::vector<std::vector<std::uint8_t>> adjacency_mtrx(n, std::vector<std::uint8_t>(n, 0));

	size_t edge = 0;
	while (edge < m) {
		size_t u, v;
		std::cin >> u >> v;

		if ((u >= 1 && u <= n) && (v >= 1 && v <= n)) {
			adjacency_mtrx[u - 1][v - 1] = 1;
		}

		++edge;
	}

	PrintAdjacencyMatrix(adjacency_mtrx);
}

int main() {
	size_t n, m;
	std::cin >> n >> m;

	Solution(n, m);
}