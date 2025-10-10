#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void Solution(std::string_view s, std::string_view t) {
    size_t i = 0, j = 0;

    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            ++i;
        }
        ++j;
    }

    std::cout << (i == s.size() ? "True" : "False") << std::endl;
}

int main() {
    std::string s, t;
    std::cin >> s >> t;

    Solution(s, t);
}