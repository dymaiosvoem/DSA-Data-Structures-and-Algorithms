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
		2) завожу массив id_relevance размера n + 1, где для каждого документа doc_id храню пару (doc_id, relevance),
		   сначала relevance = 0;
		3) для каждого уникального слова запроса прохожу по всем парам (doc_id, freq) в word_id_freq[word]
		   и увеличиваю id_relevance[doc_id].second на freq, так я накапливаю релевантность документа;
		4) частично сортирую id_relevance[1...n] с помощью std::partial_sort так, чтобы первые 5 элементов были:
			-по убыванию релевантности;
			-если релевантности документов совпадают, то по возрастанию их порядковых номеров в базе.

	Печатаю по итоговому массиву id_relevance только первые 5 документов с ненулевой релевантностью.

	-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
	Корректность ParsingDocuments(std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq, size_t n):
		-если слово встречается в документе с номером doc_id freq раз, то в word_id_freq[word] у нас будет ровно одна запись (doc_id, freq);
		-если слово не встречается в документе doc_id, то такие пары в word_id_freq[word] не сохраняются.

	Корректность ProcessQuery(const std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq, size_t n):
		-сохраняются только уникальные слова запроса, поэтому если слово встречается несколько раз в запросе,
		 оно будет учитываться только 1 раз;
		-для каждого уникального слова запроса я прохожу по всем парам (doc_id, freq) в word_id_freq[word] и
		 увеличиваю id_relevance[doc_id].second на freq. поэтому после окончания цикла id_relevance[doc_id].second равен сумме
		 частот всех уникальных слов запроса в документе doc_id;
		-std::partial_sort упорядочивает подмассив id_relevance[1...n] так:
			1) по убыванию релевантности;
			2) если релевантности документов совпадают, то по возрастанию их порядковых номеров в базе.

	Корректность PrintResult(const std::vector<std::pair<size_t, size_t>>& id_relevance, size_t n):
		-функция выводит не более пяти самых релевантных документов.

	-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
	Пусть:
		1) n - количество документов;
		2) m - количество запросов;
		3) L_q_max - максимальное число слов в запросе;
		4) L_q - количество слов в одном конкретном запросе.

	Тогда:
		1) ParsingDocuments:
			Максимальная длина одного документа ограничивается константой в 1000 символов, тогда парсинг всех документов
			работает за O(n).
		2) ProcessQuery(обработка одного запроса длины L_q):
			-разбор строки запроса и сохранение уникальных слов: O(L_q);
			-для каждого уникального слова запроса перебираю все документы, в которых это слово встречается,
			 в худшем случае каждое из L_q слов запроса встречается во всех n документах, поэтому эта часть работает
			 за: O(L_q * n);
			-далее вызываю std::partial_sort по массиву из n документов для выбора 5 (константа) самых релевантных: O(n).

			Итог для обработки одного запроса: O(L_q * n).
		3) PrintResult: O(1), печатаю не более 5 документов.

	Итог для m запросов в худшем случае, когда каждый запрос имеет максимальную длину L_q == L_q_max:
		O(m * (L_q_max * n)).

	Общий итог: O(n + m * (L_q_max * n)).

	-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
	Пусть:
		1) n - количество документов;
		2) L_q_max - максимальное число слов в запросе;
		3) L_q - количество слов в одном конкретном запросе.

	Тогда:
		1) ParsingDocuments:
			Для каждого слова из документа сохраняю пары (doc_id, freq), всего n документов, длина строки - константа
			в 1000 символов (ее не учитываю): O(n).
		2) ProcessQuery:
			-сохраняю уникальные слова, в худшем случае в запросе все слова будут уникальными: O(L_q);
			-завожу массив id_relevance размера n + 1, где для каждого doc_id храню пару (doc_id, relevance): O(n).

			В худшем случае, когда запрос имеет максимальную длину L_q == L_q_max: O(L_q_max + n).
		3) PrintResult: O(1).

	Итог: O(n + L_q_max + n) = O(n + L_q_max);
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

std::vector<std::pair<size_t, size_t>> ProcessQuery(const std::unordered_map<std::string, std::vector<IdAndFreq>>& word_id_freq, size_t n) {
	std::unordered_set<std::string> uniq_words = ParsingQuery();

	std::vector<std::pair<size_t, size_t>> id_relevance(n + 1);
	for (size_t doc_id = 1; doc_id <= n; ++doc_id) {
		id_relevance[doc_id].first = doc_id;
		id_relevance[doc_id].second = 0;
	}

	for (const auto& word : uniq_words) {
		auto it = word_id_freq.find(word);

		if (it != word_id_freq.end()) {
			for (const auto& [doc_id, freq] : it->second) {
				id_relevance[doc_id].second += freq;
			}
		}
	}

	const size_t to_move = std::min<size_t>(5, n);

	auto first = id_relevance.begin() + 1;
	auto middle = first + to_move;
	auto last = id_relevance.end();

	std::partial_sort(first, middle, last, [](const auto& lhs, const auto& rhs) {
		if (lhs.second == rhs.second) {
			return lhs.first < rhs.first;
		}

		return lhs.second > rhs.second;
		});

	return id_relevance;
}

void PrintResult(const std::vector<std::pair<size_t, size_t>>& id_relevance, size_t n) {
	size_t end_printing = std::min<size_t>(5, n);
	bool space = false;

	auto it = id_relevance.begin() + 1;

	for (size_t i = 0; i < end_printing; ++i, ++it) {
		if (it->second == 0) {
			break;
		}

		if (space) {
			std::cout << ' ' << it->first;
		} else {
			std::cout << it->first;
			space = true;
		}
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
		auto result = ProcessQuery(word_id_freq, n);

		PrintResult(result, n);
	}
}

int main() {
	Solution();
}