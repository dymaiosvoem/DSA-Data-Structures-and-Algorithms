/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются ребра в виде троек чисел source, destination, weight.

	Сохраняю входные данные в граф (списки смежности - adjacency_lists_), где у вершин хранятся инцидентные ребра Edge - { to, weight }.

	Делаю все вершины графа added_vertices_ == false и стартую поиск MST с вершины 1, вызывая AddVertex(1). Помечаю вершину 1 из added_vertices_ как добавленную
	и складываю в pq_ (max-heap -> weight) инцидентные ребра вершины 1, ведущие в вершины edge.to_ и которые added_vertices_[edge.to_] == false.
	Беру максимальное по весу из pq_, если added_vertices_[edge.to_] == false, то max_mst_weight_ += edge.weight_ и AddVertex(edge.to_),
	иначе считаю что это был мусор и ничего не делаю. Все повторяется пока выполняются 2 условия: 1) added_count_ != added_vertices_.size() - 1;
	2) !pq_.empty().

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: после каждого AddVertex(v) вершина v из added_vertices_ помечается как true, а в pq_ добавляются все ребра из v, ведущие в вершины из added_vertices_,
	которые помечены как false (ребра, ведущие в уже добавленные вершины added_vertices_[v] == true, считаются мусором и отбрасываются).

	На каждой итерации FindMst выбирается ребро максимального веса из pq_. Каждый успешный шаг добавляет новую вершину в остов, поэтому при связном
	графе будут добавлены все вершины и полученный вес равен весу максимального остова.

	Если граф несвязный, очередь опустеет и added_count_ != added_vertices_.size() - 1, то максимального остовного дерева не существует и вывожу "Oops! I did it again".

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть V - все вершины, E - все ребра.

	Построение adjacency_lists_: O(|V| + |E|);

	Построение added_vertices_: O(|V|);

	Добавление вершины AddVertex: большинство операций за O(1), кроме цикла O(deg(v) * log |E|)

	FindMst: 1) каждое ребро может быть добавлено в pq_ не более одного раза -> O(|E| * log |E|);
			 2) каждое добавленное в pq_ ребро будет извлечено не более одного раза -> O(|E| * log |E|);

			 Итог FindMst: O(|E| * log |E|).

	Общий итог: O((|V| + |E|) + |E| * log |E|).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Хранение adjacency_lists_: O(|V| + |E|);
	Хранение added_vertices_: O(|V|);
	Хранение pq_: O(|E|);

	Итог: O(|V| + |E|)
*/

#include <iostream>
#include <queue>
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
		: adjacency_lists_(size) {
	}

	std::vector<std::vector<Edge>> adjacency_lists_;
};

struct PriorityQueueComparator {
	bool operator()(const Edge& lhs, const Edge& rhs) const {
		return lhs.weight_ < rhs.weight_;
	}
};

struct MstState {
	explicit MstState(size_t size)
		: added_vertices_(size, false),
		added_count_(0),
		max_mst_weight_(0) {
	}

	void AddVertex(const Graph& graph, size_t vertex) {
		added_vertices_[vertex] = true;
		++added_count_;

		for (const auto& edge : graph.adjacency_lists_[vertex]) {
			if (!added_vertices_[edge.to_]) {
				pq_.push(edge);
			}
		}
	}

	void FindMst(const Graph& graph) {
		AddVertex(graph, 1);

		while (added_count_ != added_vertices_.size() - 1 && !pq_.empty()) {
			const auto edge = pq_.top();
			pq_.pop();

			if (!added_vertices_[edge.to_]) {
				max_mst_weight_ += edge.weight_;

				AddVertex(graph, edge.to_);
			}
		}
	}

	size_t GetMaxMstWeight() const {
		return max_mst_weight_;
	}

	bool IsSpanningBuilt() const {
		return added_count_ == added_vertices_.size() - 1;
	}

	std::priority_queue<Edge, std::vector<Edge>, PriorityQueueComparator> pq_;

	std::vector<bool> added_vertices_;
	size_t added_count_;

	size_t max_mst_weight_;
};

void Solution(size_t vertices, size_t edges) {
	Graph graph(vertices + 1);

	for (size_t edge_idx = 0; edge_idx < edges; ++edge_idx) {
		size_t source, destination, weight;
		std::cin >> source >> destination >> weight;

		graph.adjacency_lists_[source].push_back(Edge(destination, weight));
		graph.adjacency_lists_[destination].push_back(Edge(source, weight));
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