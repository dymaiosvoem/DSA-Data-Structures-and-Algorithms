/*
	-- ПРИНЦИП РАБОТЫ --
	Храню матрицу размером (rows + 1) х (columns + 1). Реальные границы [1, rows] и [1, columns].

	Обхожу все клетки двойным циклом, когда встречаю землю, а не воду, то помечаю землю водой и делаю поиск в ширину.
	При обходе в ширину, если в реальных границах матрицы соседние клетки (Coordinates(-1, 0), Coordinates(1, 0), Coordinates(0, -1),
	Coordinates(0, 1)) клетки земля, кладу в queue и помечаю их водой для дальнейшей обработки и поиска их соседей. Поиск в ширину
	работает, пока !queue.empty(), а сам алгоритм поиска островов, пока не обойду все клетки.

	В конце получаю пару [number_islands, max_island_size] и вывожу ее.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант поиска островов: как только клетка земли добавляется в queue BFS, она помечается водой. поэтому каждая клетка земли может
	быть добавлена и обработана не более одного раза.

	функции:
		1) std::pair<size_t, size_t> FindIslands(...): перебирает все клетки матрицы в реальных ее границах.
			1. если клетка вода, то она не может быть началом нового острова;
			2. если клетка земля, то она становится началом нового острова.

		2) void BFS(...): BFS берет клетку из очереди и рассматривает ее 4 соседей. сосед обрабатывается только если:
			1. он лежит в реальных границах матрицы;
			2. это земля.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть R = rows, C = columns.

	1) std::pair<size_t, size_t> FindIslands(...): перебор всех клеток O(R * C);

	2) void BFS(...): каждая клетка push() и pop() из queue не более одного раза за O(1), нахождение соседей за O(1).
	в худшем случае вся матрица - один цельный остров O(R * C);

	Итог: O(R * C)

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Храниние матрицы field: O(R + 1 * C + 1);
	queue BFS в худшем случае: O(R * C);
	Остальные поменные: O(1).

	Итог: O(R * C)
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

struct IslandContext {
	explicit IslandContext()
		: number_islands_(0),
		max_island_size_(0) {
	}

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

void BFS(IslandContext& island_context, std::vector<std::vector<int>>& field, int x, int y) {
	std::queue<Coordinates> queue;
	size_t island_size = 0;

	queue.push(Coordinates(x, y));

	field[y][x] = 0;

	while (!queue.empty()) {
		auto current = queue.front();
		queue.pop();

		++island_size;

		static const std::array<Coordinates, 4> steps = {
			Coordinates(-1, 0),
			Coordinates(1, 0),
			Coordinates(0, -1),
			Coordinates(0, 1)
		};

		for (size_t dir_idx = 0; dir_idx < steps.size(); ++dir_idx) {
			int nx = current.x_ + steps[dir_idx].x_;
			int ny = current.y_ + steps[dir_idx].y_;

			if (ny > 0 && ny < (int)field.size() && nx > 0 && nx < (int)field[ny].size() && field[ny][nx] != 0) {
				queue.push(Coordinates(nx, ny));

				field[ny][nx] = 0;
			}
		}
	}

	island_context.max_island_size_ = std::max(island_size, island_context.max_island_size_);
}

std::pair<size_t, size_t> FindIslands(std::vector<std::vector<int>>& field) {
	IslandContext island_context;

	for (int y = 1; y < (int)field.size(); ++y) {
		for (int x = 1; x < (int)field[y].size(); ++x) {

			if (field[y][x] == 0) {
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

	auto [number_islands, max_island_size] = FindIslands(field);

	std::cout << number_islands << ' ' << max_island_size << '\n';
}

int main() {
	size_t rows, columns;
	std::cin >> rows >> columns;

	Solution(rows, columns);
}