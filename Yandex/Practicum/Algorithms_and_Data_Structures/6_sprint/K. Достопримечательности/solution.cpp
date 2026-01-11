#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct Edge {
	explicit Edge(size_t to, size_t weight)
		: to_(to),
		weight_(weight) {
	}

	size_t to_;
	size_t weight_;
};

struct PriorityQueueComparator {
	bool operator()(const std::pair<int, size_t>& lhs, const std::pair<int, size_t>& rhs) const {
		return lhs.first > rhs.first;
	}
};

void PrintDistance(const std::vector<int>& distance) {
	bool space = false;

	for (size_t i = 1; i < distance.size(); ++i) {
		if (space) {
			std::cout << ' ' << (distance[i] == INT_MAX ? -1 : distance[i]);
		} else {
			std::cout << (distance[i] == INT_MAX ? -1 : distance[i]);

			space = true;
		}
	}

	std::cout << '\n';
}

void Solution(size_t vertices_count, size_t edges_count) {
	/*
		Time Complexity: O(|V| * (|V| + |E| log |E|))
		Memory Complexity: O(|V| + |E|)
	*/
	std::vector<std::vector<Edge>> adjacency_list_(vertices_count + 1);

	for (size_t edge = 0; edge < edges_count; ++edge) {
		size_t source, destination, weight;
		std::cin >> source >> destination >> weight;

		adjacency_list_[source].push_back(Edge(destination, weight));
		adjacency_list_[destination].push_back(Edge(source, weight));
	}

	for (size_t start = 1; start <= vertices_count; ++start) {
		std::vector<int> distance(vertices_count + 1, INT_MAX);

		std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, PriorityQueueComparator> pq;

		pq.push({ 0, start });
		distance[start] = 0;

		while (!pq.empty()) {
			auto [queued_dist, vertex] = pq.top();
			pq.pop();

			if (queued_dist != distance[vertex]) {
				continue;
			}

			if (distance[vertex] == INT_MAX) {
				continue;
			}

			for (auto& [to, weight] : adjacency_list_[vertex]) {
				if (distance[to] > distance[vertex] + static_cast<int>(weight)) {
					distance[to] = distance[vertex] + static_cast<int>(weight);
					pq.push({ distance[to], to });
				}
			}
		}

		PrintDistance(distance);
	}
}

int main() {
	size_t vertices_count, edges_count;
	std::cin >> vertices_count >> edges_count;

	Solution(vertices_count, edges_count);
}