#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct IdAndFreq {
	size_t doc_id = 0;
	size_t freq = 0;
};

std::vector<std::string> SplitBySpace(const std::string& str) {
	std::vector<std::string> words;
	std::string word;

	for (char w : str) {
		if (w == ' ') {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		} else {
			word += w;
		}
	}

	if (!word.empty()) {
		words.push_back(word);
	}

	return words;
}

void ParsingDocuments(std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		std::string doc;
		std::getline(std::cin >> std::ws, doc);

		std::unordered_map<std::string, size_t> word_freq;

		std::vector<std::string> words = SplitBySpace(doc);
		word_freq.reserve(words.size());

		for (const auto& word : words) {
			++word_freq[word];
		}

		for (const auto& [key, value] : word_freq) {
			word_id_freq[key].emplace_back(IdAndFreq{ i + 1, value });
		}
	}
}

std::unordered_set<std::string> ParsingQuery() {
	std::string query;
	std::getline(std::cin >> std::ws, query);

	std::unordered_set<std::string> uniq_words;

	std::vector<std::string> words = SplitBySpace(query);
	uniq_words.reserve(words.size());

	for (const auto& word : words) {
		uniq_words.emplace(word);
	}

	return uniq_words;
}

std::vector<std::pair<size_t, size_t>> ProcessQuery(const std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq) {
	std::unordered_set<std::string> uniq_words = ParsingQuery();

	std::unordered_map<size_t, size_t> id_relevance;

	for (const auto& word : uniq_words) {
		auto it = word_id_freq.find(word);

		if (it != word_id_freq.end()) {
			for (const auto& [doc_id, freq] : it->second) {
				id_relevance[doc_id] += freq;
			}
		}
	}

	std::vector<std::pair<size_t, size_t>> result;
	result.reserve(id_relevance.size());

	for (const auto& [doc_id, relevance] : id_relevance) {
		result.emplace_back(doc_id, relevance);
	}

	std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
		if (left.second == right.second) {
			return left.first < right.first;
		}

		return left.second > right.second;
		});

	return result;
}

void PrintResult(const std::vector<std::pair<size_t, size_t>>& result) {
	size_t printed = 0;
	bool space = false;

	for (const auto& [key, value] : result) {
		if (printed == 5) {
			break;
		}

		if (space) {
			std::cout << ' ' << key;
		} else {
			std::cout << key;
			space = true;
		}

		++printed;
	}

	std::cout << '\n';
}

void Solution() {
	/*
		Time Complexity:   ParsingDocuments - O(L_d), L_d - length_documents

						   ProcessQuery - O(L_q) + O(P) + O(R * log R),
						   L_q - length_queries,
						   P - количество (слово, документ) - пар, по которым прошелся
						   R - количество документов с ненулевой релевантностью, size_of(result)

						   PrintResult - O(1), печатаю не более 5 документов

						   Result = O(L_q) + O(P) + O(R * log R);

		Memory Complexity: ParsingDocuments: O(U_docs) + O(P_docs) = O(P_docs),
						   U_docs - количество уникальных слов во всех документах
						   P_docs - количество всех пар (слово, IdAndFreq)

						   ProcessQuery - O(U_q) + O(I) + O(S),
						   U_q - количество уникальных слов запроса;
						   I - количество пар (id, relevance);
						   S - количество отсортированных пар (id, relevance)

						   PrintResult - O(1)

						   Result = O(U_q) + O(I) + O(S);
	*/
	size_t n;
	std::cin >> n;

	std::unordered_map<std::string, std::vector<IdAndFreq>> word_id_freq;

	ParsingDocuments(word_id_freq, n);

	size_t m;
	std::cin >> m;

	for (size_t j = 0; j < m; ++j) {
		auto result = ProcessQuery(word_id_freq);

		PrintResult(result);
	}
}

int main() {
	Solution();
}