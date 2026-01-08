#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

enum Color {
	WHITE,
	GREY,
	BLACK
};

struct VerticesContext {
	explicit VerticesContext(size_t size)
		: colors_(size, Color::WHITE) {
	}

	std::vector<Color> colors_;
};

struct GraphContext {
	explicit GraphContext(size_t size)
		: adjacency_list_(size) {
	}

	void SortAdjLists() {
		for (size_t vertex = 1; vertex < adjacency_list_.size(); ++vertex) {
			std::sort(adjacency_list_[vertex].begin(), adjacency_list_[vertex].end());
		}
	}

	std::vector<std::vector<size_t>> adjacency_list_;
};

std::vector<size_t> BFS(GraphContext& graph_context, VerticesContext& vertices_context, size_t vertex) {
	std::queue<size_t> planned;

	planned.push(vertex);
	vertices_context.colors_[planned.front()] = Color::GREY;

	std::vector<size_t> order;

	while (!planned.empty()) {
		size_t current = planned.front();
		planned.pop();

		for (auto v : graph_context.adjacency_list_[current]) {
			if (vertices_context.colors_[v] == Color::WHITE) {
				vertices_context.colors_[v] = Color::GREY;

				planned.push(v);
			}
		}

		vertices_context.colors_[current] = Color::BLACK;
		order.push_back(current);
	}

	return order;
}

void PrintResult(const std::vector<size_t>& result) {
	for (size_t i = 0; i < result.size(); ++i) {
		if (i) {
			std::cout << ' ' << result[i];
		} else {
			std::cout << result[i];
		}
	}

	std::cout << '\n';
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity: O(|V| + |E| + sum(deg(v) log deg(v)))
		Memory Complexity: O(|V| + |E|) - adj_list, colors_
	*/
	GraphContext graph_context(vertices + 1);

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		graph_context.adjacency_list_[source].push_back(destination);
		graph_context.adjacency_list_[destination].push_back(source);
	}

	graph_context.SortAdjLists();

	size_t vertex;
	std::cin >> vertex;

	VerticesContext vertices_context(vertices + 1);
	auto result = BFS(graph_context, vertices_context, vertex);

	PrintResult(result);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t vertices, edges;
	std::cin >> vertices >> edges;

	Solution(vertices, edges);
}