/*
	-- ПРИНЦИП РАБОТЫ --
	Делаю парсинг документов в хеш-таблицу (std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq):
	иду по документам по очереди:
		1) паршу документ на слова;
		2) сохраняю частоту слов в документе;
		3) переношу в хеш-таблицу, где:
			-key(std::string): встречающееся слово, одинаковые слова будут складываться в тот же key;
			-value(std::vector<IdAndFreq>): храню список пар (doc_id, freq) - сколько раз key встретилось в doc_id.

	Обрабатываю запросы по очереди:
		1) сохраняю уникальные слова запроса;
		2) иду по уникальным словам и накапливаю для каждого документа пару (id, relevance),
		   где релевантность документа - сумма частот уникальных слов запроса в этом документе;
		3) перекладываю накопленные значения в пары (id, relevance) в std::vector<std::pair<size_t, size_t>> result,
		   чтобы можно было отсортировать;
		4) сортирую result:
			-по убыванию релевантности;
			-при равной релевантности - по возрастанию id.

	Печатаю по отсортированному результату, только первые 5 самых релевантных документов.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Корректность ParsingDocuments(std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq, size_t n):
		-если слово встречается в документе с номером doc_id freq раз, то в word_id_freq[word] у нас будет ровно одна запись (doc_id, freq);
		-если слово не встречается в документе doc_id, то такие пары в word_id_freq[word] не сохраняются.

	Корректность ProcessQuery(const std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq):
		-сохраняются только уникальные слова запроса, поэтому если слово встречается несколько раз в запросе,
		 оно будет учитываться только 1 раз;
		-для каждого уникального слова запроса я прохожу по всем парам (doc_id, freq) в word_id_freq[word] и
		 увеличиваю id_relevance[doc_id] на freq. поэтому после окончания цикла id_relevance[doc_id] равен сумме
		 частот всех уникальных слов запроса в документе doc_id;
		-перекладываю пары (doc_id, relevance) в std::vector<std::pair<size_t, size_t>> result, после чего сортирую
		 их по убыванию релевантности / при равной релевантности - по возрастанию id;
		-возвращаю result для PrintResult.

	Корректность PrintResult(const std::vector<std::pair<size_t, size_t>>& result):
		-функция выводит не более пяти самых релевантных документов отсортированного result.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть:
		1) n - количество документов;
		2) m - количество запросов;
		3) L_d_max - максимальное количество слов в одном документе;
		4) L_q - количество слов в одном запросе;
		5) L_q_max - максимальное число слов в запросе среди всех m.

	Тогда:
		1) ParsingDocuments: O(n * L_d_max);
		2) ProcessQuery: O(L_q) - разбор запроса и сохранение уникальных слов;
						 O(L_q * n) - уникальное слово в худшем случае встречается во всех n документах;
						 O(n * log n) - в худшем случае, в соритровку попадут все n;
		3) PrintResult: O(1), печатаю не более 5 документов.

	Все это делается для одного запроса, всего m запросов: O(m * (L_q + L_q * n + n * log n)).

	Итог: O(n * L_d_max + m * (L_q + L_q * n + n * log n)).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Пусть:
		1) n - количество документов;
		2) L_d_max - максимальное количество слов в одном документе;
		3) L_q - количество слов в одном запросе;
		4) L_q_max - максимальное число слов в запросе среди всех m.

	Тогда:
		1) ParsingDocuments: O(n * L_d_max) - храню частоты слов в документах, сохраняя до этого
		                     пары (doc_id, freq);
		2) ProcessQuery: O(L_q) - сохраняю уникальные слова, в худшем случае в запросе все слова
						 будут уникальными;
						 O(n) - в id_relevance и result каждый doc_id может появиться не больше одного раза;
		3) PrintResult: O(1).

	Итог: O(n * L_d_max + L_q + n);
*/

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