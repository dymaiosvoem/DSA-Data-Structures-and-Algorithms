/*
	-- ПРИНЦИП РАБОТЫ --

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct IslandContext {
	explicit IslandContext(size_t size)
		: visited_(size, false),
		number_islands_(0),
		max_island_size_(0) {
	}

	bool IsVisited(size_t id) const {
		return visited_[id];
	}

	std::vector<bool> visited_;
	size_t number_islands_;
	size_t max_island_size_;
};

struct Coordinates {
	explicit Coordinates(int x, int y)
		: x_(x),
		y_(y) {
	}

	int x_;
	int y_;
};

void BFS(IslandContext& island_context, const std::vector<std::vector<int>>& field, int x, int y) {
	std::queue<Coordinates> queue;
	size_t island_size = 0;

	queue.push(Coordinates(x, y));

	size_t current_id = static_cast<size_t>((y - 1) * (field[y].size() - 1) + x);
	island_context.visited_[current_id] = true;

	while (!queue.empty()) {
		auto current = queue.front();
		queue.pop();

		++island_size;


		std::vector<Coordinates> neighbors = {
			Coordinates(current.x_ - 1, current.y_),
			Coordinates(current.x_ + 1, current.y_),
			Coordinates(current.x_, current.y_ - 1),
			Coordinates(current.x_, current.y_ + 1) };

		for (size_t idx = 0; idx < neighbors.size(); ++idx) {

		}

		/*if (current.x_ - 1 > 0 && field[current.y_][current.x_ - 1] != 0 && !island_context.IsVisited((current.y_ - 1)* (field[current.y_].size() - 1) + current.x_ - 1)) {
			queue.push(Coordinates(current.x_ - 1, current.y_));
			island_context.visited_[(current.y_ - 1) * (field[current.y_].size() - 1) + current.x_ - 1] = true;
		}

		if (current.x_ + 1 < field[current.y_].size() && field[current.y_][current.x_ + 1] != 0 && !island_context.IsVisited((current.y_ - 1) * (field[current.y_].size() - 1) + current.x_ + 1)) {
			queue.push(Coordinates(current.x_ + 1, current.y_));
			island_context.visited_[(current.y_ - 1) * (field[current.y_].size() - 1) + current.x_ + 1] = true;
		}

		if (current.y_ - 1 > 0 && field[current.y_ - 1][current.x_] != 0 && !island_context.IsVisited((current.y_ - 2) * (field[current.y_].size() - 1) + current.x_)) {
			queue.push(Coordinates(current.x_, current.y_ - 1));
			island_context.visited_[(current.y_ - 2) * (field[current.y_].size() - 1) + current.x_] = true;
		}

		if (current.y_ + 1 < field.size() && field[current.y_ + 1][current.x_] != 0 && !island_context.IsVisited(current.y_ * (field[current.y_].size() - 1) + current.x_)) {
			queue.push(Coordinates(current.x_, current.y_ + 1));
			island_context.visited_[current.y_ * (field[current.y_].size() - 1) + current.x_] = true;
		}*/
	}

	island_context.max_island_size_ = std::max(island_size, island_context.max_island_size_);
}

std::pair<size_t, size_t> FindIslands(IslandContext& island_context, const std::vector<std::vector<int>>& field) {
	for (int y = 1; y < field.size(); ++y) {
		for (int x = 1; x < field[y].size(); ++x) {
			size_t id = static_cast<size_t>((y - 1) * (field[y].size() - 1) + x);

			if (field[y][x] == 0 || island_context.visited_[id]) {
				continue;
			}

			++island_context.number_islands_;
			BFS(island_context, field, x, y);
		}
	}

	return { island_context.number_islands_, island_context.max_island_size_ };
}

void Solution(size_t rows, size_t columns) {
	std::vector<std::vector<int>> field(rows + 1, std::vector<int>(columns + 1, 0));

	for (size_t i = 1; i < field.size(); ++i) {
		for (size_t j = 1; j < field[i].size(); ++j) {
			char ch;
			std::cin >> ch;

			field[i][j] = (ch == '#') ? 1 : 0;
		}
	}

	IslandContext island_context(rows * columns + 1);

	auto [number_islands, max_island_size] = FindIslands(island_context, field);

	std::cout << number_islands << ' ' << max_island_size << '\n';
}

int main() {
	size_t rows, columns;
	std::cin >> rows >> columns;

	Solution(rows, columns);
}