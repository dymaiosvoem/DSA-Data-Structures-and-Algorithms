#include <algorithm>
#include <iostream>
#include <string>

bool IsAllowedByOneEdit(const std::string& passport_name, const std::string& name_from_base) {
	/*
		Time Complexity: O(N), N - max(|passport|, |base|)
		Memory Complexity: O(1)
	*/
	size_t passport_len = passport_name.length(), base_len = name_from_base.length();
	size_t count_edits = 0;

	if (passport_len == base_len) {
		size_t i = 0;

		while (i < base_len) {
			if (passport_name[i] != name_from_base[i]) {
				++count_edits;
			}

			++i;
		}

	} else {
		if (std::max(passport_len, base_len) - std::min(passport_len, base_len) > 1) {
			return false;
		}

		const std::string* long_str; const std::string* short_str;

		if (passport_len > base_len) {
			long_str = &passport_name;
			short_str = &name_from_base;
		} else {
			long_str = &name_from_base;
			short_str = &passport_name;
		}

		size_t long_idx = 0, short_idx = 0;

		while (long_idx < long_str->length() && short_idx < short_str->length()) {
			if ((*long_str)[long_idx] != (*short_str)[short_idx]) {
				++count_edits;
				++long_idx;
			} else {
				++long_idx;
				++short_idx;
			}
		}
	}

	return count_edits <= 1;
}

int main() {
	std::string passport_name, name_from_base;
	std::cin >> passport_name >> name_from_base;

	if (IsAllowedByOneEdit(passport_name, name_from_base)) {
		std::cout << "OK" << '\n';
	} else {
		std::cout << "FAIL" << '\n';
	}
}