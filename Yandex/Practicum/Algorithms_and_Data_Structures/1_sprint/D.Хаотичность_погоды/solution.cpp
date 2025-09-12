#include <iostream>
#include <vector>

void FindNumberChaoticDays(const std::vector<int>& temperatures) {
    /*
    Time Complexity: O(N)
    Memory Complexity: O(1)
    */

    if (temperatures.size() == 1) {
        std::cout << 1 << '\n';
        return;
    }

    int chaotic_days = 0;
    size_t last_day = temperatures.size() - 1;

    for (size_t index = 0; index < temperatures.size(); ++index) {
        if ((index == 0 && temperatures[index] > temperatures[index + 1])
            || (index == last_day && temperatures[index] > temperatures[index - 1])) {
            chaotic_days += 1;
        } else if ((index > 0 && index < last_day) && temperatures[index] > temperatures[index + 1]
            && temperatures[index] > temperatures[index - 1]) {
            chaotic_days += 1;
        }
    }
    std::cout << chaotic_days << '\n';
}

int main() {
    size_t num_of_days;
    std::cin >> num_of_days;

    std::vector<int> temp_per_day;
    temp_per_day.reserve(num_of_days);

    for (size_t i = 0; i < num_of_days; ++i) {
        int temp;
        std::cin >> temp;
        temp_per_day.push_back(temp);
    }

    FindNumberChaoticDays(temp_per_day);
}