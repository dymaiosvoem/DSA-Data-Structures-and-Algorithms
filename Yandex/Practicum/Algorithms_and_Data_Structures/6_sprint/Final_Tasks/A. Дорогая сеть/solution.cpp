/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются ребра в виде троек чисел source, destination, weight.

	Сохраняю входные данные в граф (списки смежности - adjacency_lists_), где у вершин хранятся инцидентные ребра
	Edge - { to, weight }.

	Делаю все вершины графа not_added_ и стартую поиск MST с вершины 1, вызывая AddVertex(1). Удаляю вершину 1 из not_added_ и складываю в
	pq_ (max-heap -> weight) инцидентные ребра вершины 1, ведущие в вершины edge.to_ и которые not_added_.count(edge.to_) > 0.
	Беру максимальное по весу из pq_, если not_added_.count(edge.to_) > 0, то max_mst_weight_ += edge.weight_ и AddVertex(edge.to_),
	иначе считаю что это был мусор и ничего не делаю. Все повторяется пока выполняются 2 условия: 1)not_added_.size() > 0; 2)!pq_.empty()

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: после каждого AddVertex(v) вершина v удаляется из not_added_, а в pq_ добавляются все ребра из v, ведущие в вершины из not_added_
	(ребра, ведущие в уже добавленные вершины, считаются мусором и отбрасываются проверкой not_added_.count(edge.to_) > 0).

	На каждой итерации FindMst выбирается ребро максимального веса из pq_. Каждый успешный шаг добавляет новую вершину в остов, поэтому при связном
	графе будут добавлены все вершины и полученный вес равен весу максимального остова.

	Если граф несвязный, очередь опустеет при непустом not_added_, поэтому максимального остовного дерева не существует и выводится «Oops! I did it again».

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть V - все вершины, E - все ребра.

	Построение adjacency_lists_: O(|V| + |E|);

	Построение not_added_: O(|V| * log |V|);

	Добавление вершины AddVertex: 1) not_added_.erase(vertex) -> O(log |V|)
								  2) not_added_.count(edge.to_) > 0 -> O(log |V|)
								  3) pq_.push(edge) -> O(log |E|)

								  За один AddVertex(v): O(log |V| + deg(v) * (log |V| + log |E|)).

	FindMst: 1) not_added_.erase вызывается не более |V| раз (внутри AddVertex) -> O(|V| * log |V|);
			 2) каждое ребро может быть добавлено в pq_ не более одного раза -> O(|E| * log |E|);
			 3) каждое добавленное в pq_ ребро будет извлечено не более одного раза -> O(|E| * log |E|);
			 4) на каждой итерации while есть проверка not_added_.count(edge.to_) -> O(|E| * log |V|).

			 Итого FindMst: O(|V| * log |V| + |E| * log |E| + |E| * log |V|).

	Общий итог: O(|V| * log |V| + |E| * log |E| + |E| * log |V|).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Хранение adjacency_lists_: O(|V| + |E|);
	Хранение not_added_: O(|V|);
	Хранение pq_: O(|E|);

	Итог: O(|V| + |E|)
*/

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
	explicit MstState(size_t size) : max_mst_weight_(0) {
		for (size_t vertex = 1; vertex < size; ++vertex) {
			not_added_.insert(vertex);
		}
	}

	void AddVertex(const Graph& graph, size_t vertex) {
		not_added_.erase(vertex);

		for (const auto& edge : graph.adjacency_lists_[vertex]) {
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