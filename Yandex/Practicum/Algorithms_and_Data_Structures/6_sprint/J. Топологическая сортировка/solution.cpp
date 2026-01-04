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

struct TopoContext {
	explicit TopoContext(size_t size)
		: adjacency_list_(size),
		colors_(size, Color::WHITE) {
	}

	std::vector<std::vector<size_t>> adjacency_list_;
	std::vector<Color> colors_;
	std::stack<size_t> order_;
};

void TopologicalDfsIterative(TopoContext& topo_context, size_t vertex) {
	std::stack<VertexInfo> stack;
	stack.push(VertexInfo(vertex, false));

	while (!stack.empty()) {
		auto current = stack.top();
		stack.pop();

		if (topo_context.colors_[current.v_] == Color::WHITE && !current.exiting_) {
			topo_context.colors_[current.v_] = Color::GREY;

			stack.push(VertexInfo(current.v_, true));

			for (auto v : topo_context.adjacency_list_[current.v_]) {
				if (topo_context.colors_[v] == Color::WHITE) {
					stack.push(VertexInfo(v, false));
				}
			}
		} else if (topo_context.colors_[current.v_] == Color::GREY && current.exiting_) {
			topo_context.colors_[current.v_] = Color::BLACK;

			topo_context.order_.push(current.v_);
		}
	}
}

void PrintOrder(std::stack<size_t>& order) {
	while (!order.empty()) {
		std::cout << order.top() << ' ';
		order.pop();
	}
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity: O(|V| + |E|)
		Memory Complexity: O(|V| + |E|)
	*/
	TopoContext topo_context(vertices + 1);

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		topo_context.adjacency_list_[source].push_back(destination);
	}

	for (size_t vertex = 1; vertex < topo_context.adjacency_list_.size(); ++vertex) {
		if (topo_context.colors_[vertex] == Color::WHITE) {
			TopologicalDfsIterative(topo_context, vertex);
		}
	}

	PrintOrder(topo_context.order_);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t n, m;
	std::cin >> n >> m;

	Solution(n, m);
}