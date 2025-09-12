#include <iostream>
#include <string>
#include <string_view>

void Solution(std::string_view line) {

    /* 
    Time Complexity: O(L), where L = line.size()
    Memory Complexity: O(1) 
    */
    
    std::string_view long_word;
    size_t max_size_word = 0;

    size_t start = 0;
    size_t end = line.size();

    while (start < end) {
        size_t space_index = line.find_first_of(' ', start);

        std::string_view tmp = line.substr(start, space_index - start);
        
        if (max_size_word < tmp.size()) {
            long_word = tmp;
            max_size_word = long_word.size();
        }


        if (space_index != std::string_view::npos) {
            start = space_index + 1;
        } else {
            break;
        }
    }

    std::cout << long_word << '\n' << max_size_word << '\n';
}

int main() {
    size_t length;
    std::cin >> length;

    std::string line;
    line.reserve(length);
    std::getline(std::cin >> std::ws, line);

    Solution(line);
}