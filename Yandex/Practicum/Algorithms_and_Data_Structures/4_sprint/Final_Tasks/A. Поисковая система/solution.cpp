#include <algorithm>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

void Solution() {
	/*
		Time Complexity:
		Memory Complexity:
	*/

}

struct IdAndFreq {
	size_t doc_id = 0;
	size_t freq = 0;
};

int main() {
	size_t n;
	std::cin >> n;

	std::unordered_map<std::string, std::vector<IdAndFreq>> word_id_freq;

	for (size_t i = 0; i < n; ++i) {
		std::string doc;
		std::getline(std::cin >> std::ws, doc);

		std::unordered_map<std::string, size_t> word_freq;

		std::string word;
		size_t start = 0;

		while (start < doc.size()) {
			if (doc[start] == ' ') {
				if (!word.empty()) {
					word_freq[word] += 1;
					word.clear();
				}
			} else {
				word += doc[start];
			}

			++start;
		}

		if (!word.empty()) {
			word_freq[word] += 1;
		}

		for (const auto& [key, value] : word_freq) {
			word_id_freq[key].emplace_back(IdAndFreq{ i + 1, value });
		}
	}

	size_t m;
	std::cin >> m;

	for (size_t j = 0; j < m; ++j) {
		std::string request;
		std::getline(std::cin >> std::ws, request);

		std::unordered_set<std::string> uniq_words;
		uniq_words.reserve(request.size());

		std::string word;
		size_t start = 0;

		while (start < request.size()) {
			if (request[start] == ' ') {
				if (!word.empty()) {
					uniq_words.emplace(word);
					word.clear();
				}
			} else {
				word += request[start];
			}

			++start;
		}

		if (!word.empty()) {
			uniq_words.emplace(word);
		}

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
			result.emplace_back(static_cast<int>(doc_id), relevance);
		}

		std::sort(result.begin(), result.end(), [&](const auto& left, const auto& right) {
			if (left.second == right.second) {
				return left.first < right.first;
			}

			return left.second > right.second;
			});

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
}