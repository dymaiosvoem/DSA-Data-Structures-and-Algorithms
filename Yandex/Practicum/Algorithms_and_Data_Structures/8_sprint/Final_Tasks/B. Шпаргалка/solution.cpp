/*
	-- ПРИНЦИП РАБОТЫ --
	На вход подаются текст и слова на которые он может разбиваться. Строю префиксное дерево по словам. 
	Отмечаю достижимые позиции в тексте и из каждой позиции пытаюсь пройти по префиксному дереву и пометить 
	новые достижимые позиции на концах найденных слов.

	Ответ: достижима ли позиция T, где T = text.length().

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Инвариант: reachable[j] хранит булево, достижима ли позиция в тексте и можно ли разбить префикс text[0..j - 1] 
	длины j на слова из бора.

	База: reachable[0] == true, потому что пустой префикс длины 0 считается разбитым.

	Переход: если reachable[i] == true, то до этой позиции встречались слова, которые разбивали префикс text[0..i - 1]
	длины i на слова из бора. Прохожу j индексом от позиции i в поисках новых разбиений, помечая reachable[j + 1] == true,
	так как слово text[i..j] найдено в боре.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	T = text.length(), W = |word|, L = max length word in trie;

	AddWord(word): 
		-добавление одного слова в бор: O(W);
		-в каждом узле ищу текущий символ (trie_[node_idx].children_.find(ch)): amortized O(1);
		-добавление нового узла: O(1).

		Итог: O(sum(W)).

	IsPossibleSplitText(text):
		-внешний цикл: проход по всем символам текста - O(T);
		-внутренний цикл: для каждой достижимой позиции из reachable делаю не больше L переходов по бору - O(L).

		Итог: O(T * L).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	В худшем случае слова будут состоять из максимальной длины - 100 символов, всего слов 1 <= n <= 100 и у них не будет
	общего префикса, значит хранение бора: O(n * L).

	Также в каждой ноде unordered_map может храниться максимальное число переходов в ней <= 26 - O(1).

	Итог: O(n * L).
*/

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