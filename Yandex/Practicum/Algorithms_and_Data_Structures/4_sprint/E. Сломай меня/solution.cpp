#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

uint64_t HashString(const std::string& s) {
	uint64_t hash = 0;

	for (char c : s) {
		hash = (hash * 1000 + static_cast<uint64_t>(c)) % 123987123;
	}

	return hash;
}

void Solution(size_t s_size) {
	std::string s;
	s.reserve(s_size);

	std::unordered_map<uint64_t, std::string> hash_and_s;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(97, 122);

	while (true) {

		while (s.size() != s_size) {
			s.push_back(static_cast<char>(distrib(gen)));
		}

		uint64_t hash = HashString(s);

		auto it = hash_and_s.find(hash);
		if (it != hash_and_s.end()) {
			if (s != it->second) {
				std::cout << s << '\n' << it->second << '\n';
				break;
			}
		} else {
			hash_and_s[hash] = s;
		}

		s.clear();
	}
}

int main() {
	size_t s_size;
	std::cin >> s_size;

	Solution(s_size);
}