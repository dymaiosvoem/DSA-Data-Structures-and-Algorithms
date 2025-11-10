#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

void Solution(std::string_view s, std::string_view t) {
	/*
		Time Complexity: O(N)
		Memory Complexity: O(1)
	*/

	if (s.size() != t.size()) {
		std::cout << "NO" << '\n';
		return;
	}

	std::unordered_map<char, char> s_t;
	s_t.reserve(26);

	std::unordered_map<char, char> t_s;
	t_s.reserve(26);

	size_t i = 0;

	while (i < s.size() && i < t.size()) {
		char ch_s = s[i];
		char ch_t = t[i];

		auto find_s_t = s_t.find(ch_s);
		auto find_t_s = t_s.find(ch_t);

		if (find_s_t == s_t.end()) {
			s_t.emplace({ ch_s, ch_t });
		} else {
			if (find_s_t->second != ch_t) {
				std::cout << "NO" << '\n';
				return;
			}
		}

		if (find_t_s == t_s.end()) {
			t_s.emplace({ ch_t, ch_s });
		} else {
			if (find_t_s->second != ch_s) {
				std::cout << "NO" << '\n';
				return;
			}
		}

		++i;
	}

	std::cout << "YES" << '\n';
}

int main() {
	std::string s, t;
	std::cin >> s >> t;

	Solution(s, t);
}