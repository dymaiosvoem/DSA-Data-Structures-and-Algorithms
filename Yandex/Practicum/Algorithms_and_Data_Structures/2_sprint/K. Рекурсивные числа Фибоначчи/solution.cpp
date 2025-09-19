#include <iostream>

size_t Solution(size_t num_commits) {
	if (num_commits == 1 || num_commits == 0) {
		return 1;
	}

	return Solution(num_commits - 1) + Solution(num_commits - 2);
}

int main() {
	size_t num_commits;
	std::cin >> num_commits;

	std::cout << Solution(num_commits) << '\n';
}