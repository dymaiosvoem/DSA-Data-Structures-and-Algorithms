#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Interval {
	explicit Interval(const std::string& start_str, const std::string& end_str, int start_min, int end_min)
		: start_str_(start_str),
		end_str_(end_str),
		start_min_(start_min),
		end_min_(end_min) {
	}

	std::string start_str_;
	std::string end_str_;
	int start_min_;
	int end_min_;
};

void Solution(size_t count_classes) {
	/*
		Time Complexity: O(N * log N)
		Memory Complexity: O(N)
	*/
	std::vector<Interval> intervals;
	intervals.reserve(count_classes);

	for (size_t i = 0; i < count_classes; ++i) {
		std::string start, end;
		std::cin >> start >> end;

		int start_minutes = 0;
		int end_minutes = 0;

		size_t dot_pos_start = start.find('.');
		size_t dot_pos_end = end.find('.');

		if (dot_pos_start != std::string::npos) {
			start_minutes = 60 * std::stoi(start.substr(0, dot_pos_start)) + std::stoi(start.substr(dot_pos_start + 1));
		} else {
			start_minutes = 60 * std::stoi(start);
		}

		if (dot_pos_end != std::string::npos) {
			end_minutes = 60 * std::stoi(end.substr(0, dot_pos_end)) + std::stoi(end.substr(dot_pos_end + 1));
		} else {
			end_minutes = 60 * std::stoi(end);
		}

		intervals.push_back(Interval(start, end, start_minutes, end_minutes));
	}

	std::sort(intervals.begin(), intervals.end(), [](const Interval& lhs, const Interval& rhs) {
		return (lhs.end_min_ < rhs.end_min_) || (lhs.end_min_ == rhs.end_min_ && lhs.start_min_ < rhs.start_min_);
		});

	std::vector<Interval> result;

	if (intervals.size() > 0) {
		result.push_back(intervals[0]);

		for (size_t j = 1; j < intervals.size(); ++j) {
			if (intervals[j].start_min_ >= result.back().end_min_) {
				result.push_back(intervals[j]);
			}
		}

		std::cout << result.size() << '\n';

		for (size_t k = 0; k < result.size(); ++k) {
			std::cout << result[k].start_str_ << ' ' << result[k].end_str_ << '\n';
		}
	} else {
		std::cout << 0 << '\n';
	}
}

int main() {
	size_t count_classes;
	std::cin >> count_classes;

	Solution(count_classes);
}