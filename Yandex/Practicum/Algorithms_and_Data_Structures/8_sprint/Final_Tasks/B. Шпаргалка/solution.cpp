#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
	std::unordered_map<char, size_t> children_;
	bool is_terminal_ = false;
};

struct Trie {
	explicit Trie(size_t size) {
		trie_.reserve(size);
		trie_.emplace_back();
	}

	void AddWord(const std::string& word) {
		size_t node_idx = 0;

		for (const auto ch : word) {
			auto it = trie_[node_idx].children_.find(ch);

			if (it == trie_[node_idx].children_.end()) {
				size_t next_node_idx = trie_.size();

				trie_.emplace_back();
				trie_[node_idx].children_[ch] = next_node_idx;

				node_idx = next_node_idx;
			} else {
				node_idx = it->second;
			}
		}

		trie_[node_idx].is_terminal_ = true;
	}

	bool IsPossibleSplitText(const std::string& text) const {
		std::vector<bool> reachable(text.size() + 1, false);
		reachable[0] = true;

		size_t node_idx = 0;
		for (size_t i = 0; i < text.length(); ++i) {
			if (reachable[i] == false) {
				continue;
			}

			for (size_t j = i; j < text.length(); ++j) {
				auto it = trie_[node_idx].children_.find(text[j]);

				if (it == trie_[node_idx].children_.end()) {
					break;
				} else {
					node_idx = it->second;
				}

				if (trie_[node_idx].is_terminal_ == true) {
					reachable[j + 1] = true;
				}
			}

			node_idx = 0;
		}

		return reachable[text.size()];
	}

	std::vector<Node> trie_;
};

void Solution() {
	std::string text;
	std::cin >> text;

	size_t n;
	std::cin >> n;

	Trie trie(n * 100 + 1);

	for (size_t i = 0; i < n; ++i) {
		std::string word;
		std::cin >> word;

		trie.AddWord(word);
	}

	if (trie.IsPossibleSplitText(text)) {
		std::cout << "YES" << '\n';
	} else {
		std::cout << "NO" << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	Solution();
}