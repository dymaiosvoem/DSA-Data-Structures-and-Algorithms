#include <iostream>
#include <string>
#include <vector>

void Solution(long long base, long long module, const std::string& s, size_t count_request) {
	std::vector<long long> hashes(s.size() + 1);
	hashes[0] = 0;

	for (size_t i = 0; i < s.size(); ++i) {
		hashes[i + 1] = (hashes[i] * base + static_cast<long long>(s[i])) % module;
	}

	std::vector<long long> degrees_base(s.size() + 1);
	degrees_base[0] = 1;

	for (size_t j = 1; j < degrees_base.size(); ++j) {
		degrees_base[j] = (degrees_base[j - 1] * base) % module;
	}

	size_t start = 0;
	long long result = 0;

	while (start < count_request) {
		size_t l, r;
		std::cin >> l >> r;

		long long a = hashes[r] - hashes[l - 1] * degrees_base[r - l + 1];

		result = (a % module + module) % module;

		std::cout << result << '\n';
		++start;
	}
}

int main() {
	long long base, module;
	std::cin >> base >> module;

	std::string s;
	std::cin >> s;

	size_t count_request;
	std::cin >> count_request;

	Solution(base, module, s, count_request);
}