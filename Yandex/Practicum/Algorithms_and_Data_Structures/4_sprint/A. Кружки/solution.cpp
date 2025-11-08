#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void Solution(size_t n) {
	std::unordered_set<std::string> clubs;
	clubs.reserve(n);

	std::vector<std::string> uniq_clubs;
	uniq_clubs.reserve(n);

	for (size_t i = 0; i < n; ++i) {
		std::string club;
		std::getline(std::cin >> std::ws, club);

		auto it = clubs.find(club);

		if (it != clubs.end()) {
			continue;
		} else {
			clubs.insert(club);
			uniq_clubs.push_back(club);
		}
	}

	for (size_t j = 0; j < uniq_clubs.size(); ++j) {
		std::cout << uniq_clubs[j] << '\n';
	}
}

int main() {
	size_t n;
	std::cin >> n;

	Solution(n);
}