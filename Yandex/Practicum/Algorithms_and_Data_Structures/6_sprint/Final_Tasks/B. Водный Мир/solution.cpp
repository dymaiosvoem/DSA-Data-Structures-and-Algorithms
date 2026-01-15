/*
	-- ПРИНЦИП РАБОТЫ --

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

*/

#include <algorithm>
#include <array>
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

	size_t CountId(int columns, int x, int y) const {
		size_t id = static_cast<size_t>(y * columns + x);

		return id;
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

	size_t current_id = island_context.CountId((int)field[y].size() - 1, x, y - 1);
	island_context.visited_[current_id] = true;

	while (!queue.empty()) {
		auto current = queue.front();
		queue.pop();

		++island_size;

		static const std::array<Coordinates, 4> dir = {
			Coordinates(-1, 0),
			Coordinates(1, 0),
			Coordinates(0, -1),
			Coordinates(0, 1)
		};

		for (size_t dir_idx = 0; dir_idx < dir.size(); ++dir_idx) {
			int nx = current.x_ + dir[dir_idx].x_;
			int ny = current.y_ + dir[dir_idx].y_;

			if (ny > 0 && ny < (int)field.size() &&
				nx > 0 && nx < (int)field[ny].size() &&
				field[ny][nx] != 0) {

				size_t id = island_context.CountId((int)field[ny].size() - 1, nx, ny - 1);

				if (!island_context.IsVisited(id)) {
					queue.push(Coordinates(nx, ny));

					island_context.visited_[id] = true;
				}
			}
		}
	}

	island_context.max_island_size_ = std::max(island_size, island_context.max_island_size_);
}

std::pair<size_t, size_t> FindIslands(IslandContext& island_context, const std::vector<std::vector<int>>& field) {
	for (int y = 1; y < (int)field.size(); ++y) {
		for (int x = 1; x < (int)field[y].size(); ++x) {
			size_t id = island_context.CountId((int)field[y].size() - 1, x, y - 1);

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