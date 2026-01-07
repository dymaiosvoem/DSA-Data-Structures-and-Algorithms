#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct GraphContext {
	explicit GraphContext(size_t size)
		: adjacency_list_(size),
		components_id_(size, -1) {
	}

	std::vector<std::vector<size_t>> adjacency_list_;
	std::vector<int> components_id_;
};

struct ComponentsContext {
	explicit ComponentsContext(size_t size) {
		flat_.reserve(size);
		offsets_.reserve(size);
		offsets_.push_back(0);
	}

	void CloseComponent() {
		offsets_.push_back(flat_.size());
	}

	size_t GetComponentsCount() const {
		return offsets_.size() > 1 ? offsets_.size() - 1 : 0;
	}

	void PrintSortedComponents() {
		const size_t components_count = GetComponentsCount();

		std::cout << components_count << '\n';

		if (components_count > 0) {
			size_t component_idx = 0;
			bool space = false;

			while (component_idx + 1 < offsets_.size()) {
				size_t begin = offsets_[component_idx];
				size_t end = offsets_[component_idx + 1];

				std::sort(flat_.begin() + begin, flat_.begin() + end);

				for (size_t i = begin; i < end; ++i) {
					if (space) {
						std::cout << ' ' << flat_[i];
					} else {
						std::cout << flat_[i];

						space = true;
					}
				}

				std::cout << '\n';

				space = false;
				++component_idx;
			}
		}
	}

	std::vector<size_t> flat_;
	std::vector<size_t> offsets_;
};

void CalculateConnectivityComponent(GraphContext& graph_context, ComponentsContext& component_context, size_t vertex) {
	std::stack<size_t> stack;
	stack.push(vertex);

	const size_t component_number = component_context.GetComponentsCount();

	while (!stack.empty()) {
		auto current = stack.top();
		stack.pop();

		if (graph_context.components_id_[current] == -1) {
			component_context.flat_.push_back(current);
			graph_context.components_id_[current] = component_number;

			for (auto v : graph_context.adjacency_list_[current]) {
				if (graph_context.components_id_[v] == -1) {
					stack.push(v);
				}
			}
		}
	}

	component_context.CloseComponent();
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity: O(|V| + |E| + |V| log |V|) - DFS + сортировка вершин внутри компоненты
		Memory Complexity: O(|V| + |E|) garph + components_id_ + flat_ + offsets_
	*/
	GraphContext graph_context(vertices + 1);

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		graph_context.adjacency_list_[source].push_back(destination);
		graph_context.adjacency_list_[destination].push_back(source);
	}

	ComponentsContext component_context(vertices + 1);

	for (size_t vertex = 1; vertex <= vertices; ++vertex) {
		if (graph_context.components_id_[vertex] == -1) {
			CalculateConnectivityComponent(graph_context, component_context, vertex);
		}
	}

	component_context.PrintSortedComponents();
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t vertices, edges;
	std::cin >> vertices >> edges;

	Solution(vertices, edges);
}