#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

enum class Color {
	WHITE,
	GREY,
	BLACK
};

struct BfsState {
	explicit BfsState(size_t size)
		: colors_(size, Color::WHITE),
		distance_(size) {
	}

	std::vector<Color> colors_;
	std::vector<size_t> distance_;
};

struct GraphContext {
	explicit GraphContext(size_t size)
		: adjacency_list_(size) {
	}

	std::vector<std::vector<size_t>> adjacency_list_;
};

size_t BFS(GraphContext& graph_context, BfsState& bfs_state, size_t starting_vertex) {
	size_t max_path_length = 0;

	std::queue<size_t> planned;

	planned.push(starting_vertex);
	bfs_state.colors_[starting_vertex] = Color::GREY;
	bfs_state.distance_[starting_vertex] = 0;

	while (!planned.empty()) {
		auto current = planned.front();
		planned.pop();

		for (auto v : graph_context.adjacency_list_[current]) {
			if (bfs_state.colors_[v] == Color::WHITE) {
				planned.push(v);

				bfs_state.colors_[v] = Color::GREY;
				bfs_state.distance_[v] = bfs_state.distance_[current] + 1;

				max_path_length = std::max(max_path_length, bfs_state.distance_[v]);
			}
		}

		bfs_state.colors_[current] = Color::BLACK;
	}

	return max_path_length;
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity: O(|V| + |E|)
		Memory Complexity: O(|V| + |E|)
	*/
	GraphContext graph_context(vertices + 1);

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		graph_context.adjacency_list_[source].push_back(destination);
		graph_context.adjacency_list_[destination].push_back(source);
	}

	size_t starting_vertex;
	std::cin >> starting_vertex;

	BfsState bfs_state(vertices + 1);
	auto max_path_length = BFS(graph_context, bfs_state, starting_vertex);

	std::cout << max_path_length << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t vertices, edges;
	std::cin >> vertices >> edges;

	Solution(vertices, edges);
}