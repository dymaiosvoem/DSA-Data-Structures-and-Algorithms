#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

enum class Color {
	WHITE,
	GREY,
	BLACK
};

struct VertexInfo {
	VertexInfo(size_t vertex, bool exiting) : v_(vertex), exiting_(exiting) {}

	size_t v_ = 0;
	bool exiting_ = false;
};

std::vector<size_t> DFS(const std::vector<std::vector<size_t>>& adjacency_list, size_t starting_vertex) {
	std::vector<size_t> result;
	result.reserve(adjacency_list.size() - 1);

	std::vector<Color> color(adjacency_list.size(), Color::WHITE);

	std::stack<VertexInfo> stack;
	stack.push(VertexInfo(starting_vertex, false));

	while (!stack.empty()) {
		auto current = stack.top();
		stack.pop();

		if (color[current.v_] == Color::GREY && current.exiting_) {
			color[current.v_] = Color::BLACK;
		} else if (color[current.v_] == Color::WHITE && !current.exiting_) {
			color[current.v_] = Color::GREY;
			stack.push(VertexInfo(current.v_, true));

			result.push_back(current.v_);

			for (auto vertex : adjacency_list[current.v_]) {
				if (color[vertex] == Color::WHITE) {
					stack.push(VertexInfo(vertex, false));
				}
			}
		}
	}

	return result;
}

void PrintResult(std::vector<size_t>& result) {
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
		Time Complexity:
		Memory Complexity:
	*/
	std::vector<std::vector<size_t>> adjacency_list(vertices + 1, std::vector<size_t>());

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t u, v;
		std::cin >> u >> v;

		adjacency_list[u].push_back(v);
		adjacency_list[v].push_back(u);
	}

	for (size_t idx = 1; idx < adjacency_list.size(); ++idx) {
		std::sort(adjacency_list[idx].begin(), adjacency_list[idx].end(), [](const size_t lhs, const size_t rhs) {
			return lhs > rhs;
			});
	}

	size_t starting_vertex;
	std::cin >> starting_vertex;

	auto result = DFS(adjacency_list, starting_vertex);

	PrintResult(result);
}

int main() {
	size_t n, m;
	std::cin >> n >> m;

	Solution(n, m);
}