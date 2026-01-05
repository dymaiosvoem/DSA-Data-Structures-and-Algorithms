#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

/*
	Подумать над архитектурой 

	struct GraphContext {
		explicit GraphContext(size_t size)
			: adjacency_list_(size),
			comp_id(size, -1) {
		}

		std::vector<std::vector<size_t>> adjacency_list_;
		std::vector<int> comp_id;
	};

	struct ComponentsContext {
		ComponentsContext()  {
			offsets_.push_back(0);
		}

		std::vector<size_t> flat_;
		std::vector<size_t> offsets_;
	};
*/

struct ComponentContext {
	explicit ComponentContext(size_t size)
		: adjacency_list_(size),
		components_list_(size),
		colors_(size, -1) {
	}

	std::vector<std::vector<size_t>> adjacency_list_;
	std::vector<std::vector<size_t>> components_list_;
	std::vector<int> colors_;
	int component_count = 1;
};

void CalculateConnectivityComponent(ComponentContext& component_context, size_t vertex) {
	std::stack<size_t> stack;
	stack.push(vertex);

	while (!stack.empty()) {
		auto current = stack.top();
		stack.pop();

		if (component_context.colors_[current] == -1) {
			component_context.colors_[current] = component_context.component_count;
			component_context.components_list_[component_context.component_count].push_back(current);

			for (auto vertex : component_context.adjacency_list_[current]) {
				if (component_context.colors_[vertex] == -1) {
					stack.push(vertex);
				}
			}
		}
	}

	++component_context.component_count;
}

void SortAndPrintComponents(ComponentContext& component_context) {
	size_t component_count = component_context.component_count - 1;
	bool space = false;

	std::cout << component_count << '\n';

	for (size_t component = 1; component <= component_count; ++component) {

		std::sort(component_context.components_list_[component].begin(), component_context.components_list_[component].end(),
			[](const size_t lhs, const size_t rhs) {
				return lhs < rhs;
			});

		for (size_t idx = 0; idx < component_context.components_list_[component].size(); ++idx) {
			if (space) {
				std::cout << ' ' << component_context.components_list_[component][idx];
			} else {
				std::cout << component_context.components_list_[component][idx];

				space = true;
			}
		}

		space = false;
		std::cout << '\n';
	}
}

void Solution(size_t vertices, size_t edges) {
	/*
		Time Complexity:
		Memory Complexity:
	*/
	ComponentContext component_context(vertices + 1);

	for (size_t edge = 0; edge < edges; ++edge) {
		size_t source, destination;
		std::cin >> source >> destination;

		component_context.adjacency_list_[source].push_back(destination);
		component_context.adjacency_list_[destination].push_back(source);
	}

	for (size_t vertex = 1; vertex <= vertices; ++vertex) {
		if (component_context.colors_[vertex] == -1) {
			CalculateConnectivityComponent(component_context, vertex);
		}
	}

	SortAndPrintComponents(component_context);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t vertices, edges;
	std::cin >> vertices >> edges;

	Solution(vertices, edges);
}