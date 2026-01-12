#include <iostream>
#include <queue>
#include <set>
#include <vector>

struct Edge {
	explicit Edge(size_t to, size_t weight)
		: to_(to),
		weight_(weight) {
	}

	size_t to_;
	size_t weight_;
};

struct Graph {
	explicit Graph(size_t size)
		: adjacency_list_(size) {
	}

	std::vector<std::vector<Edge>> adjacency_list_;
};

struct PriorityQueueComparator {
	bool operator()(const Edge& lhs, const Edge& rhs) const {
		return lhs.weight_ < rhs.weight_;
	}
};

struct MstState {
	explicit MstState(size_t size) : max_mst_weight_(0) {
		for (size_t vertex = 1; vertex < size; ++vertex) {
			not_added_.insert(vertex);
		}
	}

	void AddVertex(const Graph& graph, size_t vertex) {
		not_added_.erase(vertex);

		for (const auto& edge : graph.adjacency_list_[vertex]) {
			if (not_added_.count(edge.to_) > 0) {
				pq_.push(edge);
			}
		}
	}

	void FindMst(const Graph& graph) {
		AddVertex(graph, 1);

		while (not_added_.size() > 0 && !pq_.empty()) {
			const auto edge = pq_.top();
			pq_.pop();

			if (not_added_.count(edge.to_) > 0) {
				max_mst_weight_ += edge.weight_;

				AddVertex(graph, edge.to_);
			}
		}
	}

	size_t GetMaxMstWeight() const {
		return max_mst_weight_;
	}

	bool IsSpanningBuilt() const {
		return not_added_.empty();
	}

	std::priority_queue<Edge, std::vector<Edge>, PriorityQueueComparator> pq_;
	std::set<size_t> not_added_;

	size_t max_mst_weight_;
};

void Solution(size_t vertices, size_t edges) {
	Graph graph(vertices + 1);

	for (size_t edge_idx = 0; edge_idx < edges; ++edge_idx) {
		size_t source, destination, weight;
		std::cin >> source >> destination >> weight;

		graph.adjacency_list_[source].push_back(Edge(destination, weight));
		graph.adjacency_list_[destination].push_back(Edge(source, weight));
	}

	MstState mst_state(vertices + 1);
	mst_state.FindMst(graph);

	if (mst_state.IsSpanningBuilt()) {
		std::cout << mst_state.GetMaxMstWeight() << '\n';
	} else {
		std::cout << "Oops! I did it again" << '\n';
	}
}

int main() {
	size_t vertices, edges;
	std::cin >> vertices >> edges;

	Solution(vertices, edges);
}