#include <algorithm>
#include <iostream>
#include <vector>

void SortAndPrintAdjacencyLists(std::vector<std::vector<size_t>>& adjacency_list) {
	for (size_t i = 1; i < adjacency_list.size(); ++i) {
		std::sort(adjacency_list[i].begin(), adjacency_list[i].end());

		std::cout << adjacency_list[i].size();

		for (size_t j = 0; j < adjacency_list[i].size(); ++j) {
			std::cout << ' ' << adjacency_list[i][j];
		}

		std::cout << '\n';
	}
}

void Solution(size_t n, size_t m) {
	/*
		Пусть N - out-degree(v)
		Time Complexity: O(m + sum{v = 1..n} N * log N)
		Memory Complexity: O(n + m)
	*/
	std::vector<std::vector<size_t>> adjacency_list(n + 1);

	size_t edge = 0;
	while (edge < m) {
		size_t u, v;
		std::cin >> u >> v;

		adjacency_list[u].push_back(v);

		++edge;
	}

	SortAndPrintAdjacencyLists(adjacency_list);
}

int main() {
	size_t n, m;
	std::cin >> n >> m;

	Solution(n, m);
}