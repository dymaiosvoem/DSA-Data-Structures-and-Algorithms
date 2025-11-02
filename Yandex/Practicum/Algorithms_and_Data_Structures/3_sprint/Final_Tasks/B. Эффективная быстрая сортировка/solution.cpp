#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Participant {
    std::string login_;
    int solved_tasks_;
    int fine_;
};

bool compare_participants(const Participant& left, const Participant& right) {
    return std::make_tuple(-left.solved_tasks_, left.fine_, left.login_)
        < std::make_tuple(-right.solved_tasks_, right.fine_, right.login_);
}

void partition_in_place(std::vector<Participant>& participants, int left, int right) {
    if (left >= right) {
        return;
    }

    Participant pivot = participants[left + (rand() % (right - left + 1))];
    int i = left, j = right;

    while (true) {
        while (compare_participants(participants[i], pivot)) {
            ++i;
        }

        while (compare_participants(pivot, participants[j])) {
            --j;
        }

        if (i >= j) {
            break;
        }

        std::swap(participants[i], participants[j]);
        ++i;
        --j;
    }

    partition_in_place(participants, left, j);
    partition_in_place(participants, j + 1, right);
}

void QuickSortInPlace(std::vector<Participant>& participants) {
    partition_in_place(participants, 0, participants.size() - 1);
}

void PrintParticipants(const std::vector<Participant>& participants) {
    for (size_t i = 0; i < participants.size(); ++i) {
        std::cout << participants[i].login_ << '\n';
    }
}

void Solution(std::vector<Participant>& participants) {
    /*
        Time Complexity: O(N log N); Worse: O(N^2)
        Memory Complexity: O(1) + T(log N)
    */
    QuickSortInPlace(participants);
    PrintParticipants(participants);
}

int main() {
    size_t count_participants;
    std::cin >> count_participants;

    std::vector<Participant> participants(count_participants);
    for (size_t i = 0; i < count_participants; ++i) {
        std::cin >> participants[i].login_ >> participants[i].solved_tasks_ >> participants[i].fine_;
    }

    Solution(participants);
}