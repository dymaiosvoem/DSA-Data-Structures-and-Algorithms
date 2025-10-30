#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/*
alla 4 100
gena 6 1000
gosha 2 90
rita 2 90
timofey 4 80


pivot = alla 4 100;
6 1000 gena | 4 100 alla ---------- false
4 80 timofey | 4 100 alla --------- true
2 90 gosha | 4 100 alla -----------
2 90 rita | 4 100 alla ------------
*/

struct Participant {
    std::string login_;
    int solved_tasks_;
    size_t fine_;
};

bool compare_participants(const Participant& left, const Participant& right) {
    return std::make_tuple(-left.solved_tasks_, left.fine_, left.login_)
        < std::make_tuple(-right.solved_tasks_, right.fine_, right.login_);
}

using Pair = std::pair<std::vector<Participant>, std::vector<Participant>>;

std::pair<std::vector<Participant>, std::vector<Participant>> partition_in_place(std::vector<Participant>& participants, Participant pivot, bool (*cmp)(const Participant& left, const Participant& right)) {
    size_t left = 0, right = participants.size() - 1;

    while (left < right) {
        while (cmp(participants[left], pivot)) {
            ++left;
        }

        while (cmp(pivot, participants[right])) {
            --right;
        }

        if (left <= right) {
            std::swap(participants[left].solved_tasks_, participants[right].solved_tasks_);
            ++left;
            --right;
        }
    }

    std::vector<Participant> left, right;

    return std::make_pair(left, right);
}

std::vector<Participant> QuickSortInPlace(std::vector<Participant>& participants) {
    if (participants.size() < 2) {
        return participants;
    }

    auto pivot = participants[rand() % participants.size()];
    partition_in_place(participants, pivot, compare_participants);
}

void Solution(std::vector<Participant>& participants) {
    auto result = QuickSortInPlace(participants);

    for (auto r : result) {
        std::cout << r.login_ << '\n';
    }
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