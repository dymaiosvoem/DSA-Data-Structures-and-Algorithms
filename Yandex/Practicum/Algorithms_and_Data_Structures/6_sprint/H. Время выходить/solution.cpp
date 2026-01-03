#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <utility>

using EntryLeave = std::pair<std::vector<size_t>, std::vector<size_t>>;

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

EntryLeave DFS(const std::vector<std::vector<size_t>>& adjacency_list) {
	size_t number_vertices = adjacency_list.size();

	size_t time = 0;
	std::vector<size_t> entry(number_vertices, 0);
	std::vector<size_t> leave(number_vertices, 0);

	std::vector<Color> colors(number_vertices, Color::WHITE);

	std::stack<VertexInfo> stack;
	stack.push(VertexInfo(1, false));

	while (!stack.empty()) {
		auto current = stack.top();
		stack.pop();

		if (colors[current.v_] == Color::GREY && current.exiting_) {
			leave[current.v_] = time++;
			colors[current.v_] = Color::BLACK;
		} else if (colors[current.v_] == Color::WHITE && !current.exiting_) {
			entry[current.v_] = time++;
			colors[current.v_] = Color::GREY;

			stack.push(VertexInfo(current.v_, true));

			for (auto vertex : adjacency_list[current.v_]) {
				if (colors[vertex] == Color::WHITE) {
					stack.push(VertexInfo(vertex, false));
				}
			}
		}
	}

	return { entry, leave };
}

void PrintResult(const EntryLeave& result) {
	size_t size = std::max(result.first.size(), result.second.size());

	for (size_t i = 1; i < size; ++i) {
		std::cout << result.first[i] << ' ' << result.second[i] << '\n';
	}
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity: O(n + m * log m)
		Memory Complexity: O(n + m)
	*/
	std::vector<std::vector<size_t>> adjacency_list(vertices + 1, std::vector<size_t>());

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		adjacency_list[source].push_back(destination);
	}

	for (size_t idx = 1; idx < adjacency_list.size(); ++idx) {
		std::sort(adjacency_list[idx].begin(), adjacency_list[idx].end(), [](const size_t lhs, const size_t rhs) {
			return lhs > rhs;
			});
	}

	auto result = DFS(adjacency_list);

	PrintResult(result);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t n, m;
	std::cin >> n >> m;

	Solution(n, m);
}