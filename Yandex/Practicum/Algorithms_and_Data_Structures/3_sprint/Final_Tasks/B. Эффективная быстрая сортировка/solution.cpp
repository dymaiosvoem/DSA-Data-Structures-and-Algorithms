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

left = -4 100 alla

-4 100 alla | -4 80 timofey
right = -4 80 timofey

timofey 4 80
gena 6 1000
gosha 2 90
rita 2 90
alla 4 100

-6 1000 gena | -4 100 alla ------- true
-2 90 gosha | -4 100 alla -------- false

left = -2 90 gosha

-4 100 alla | -2 90 rita --------- true
-4 100 alla | -2 90 gosha -------- true
-4 100 alla | -6 1000 gena ------- false
right = -6 1000 gena

timofey 4 80
gena 6 1000
gosha 2 90
rita 2 90
alla 4 100

left = 2, right = 1

надо делать все in place, подумать над тем как брать pivot c left right диапозон
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

size_t partition_in_place(std::vector<Participant>& participants, size_t left, size_t right, bool (*cmp)(const Participant& left, const Participant& right)) {
    Participant pivot = participants[left + rand() % (right - left + 1)];

    while (left < right) {
        while (cmp(participants[left], pivot)) {
            ++left;
        }

        while (cmp(pivot, participants[right])) {
            --right;
        }

        if (left <= right) {
            std::swap(participants[left], participants[right]);
            ++left;
            --right;
        }
    }

    return right;
}

void QuickSort(std::vector<Participant>& participants, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t i = partition_in_place(participants, left, right, compare_participants);
    QuickSort(participants, left, i);

    QuickSort(participants, i + 1, right);
}

void PrintParticipants(const std::vector<Participant>& participants) {
    for (size_t i = 0; i < participants.size(); ++i) {
        std::cout << participants[i].login_ << '\n';
    }
}

int main() {
    size_t count_participants;
    std::cin >> count_participants;

    std::vector<Participant> participants(count_participants);
    for (size_t i = 0; i < count_participants; ++i) {
        std::cin >> participants[i].login_ >> participants[i].solved_tasks_ >> participants[i].fine_;
    }

    size_t left = 0, right = count_participants - 1;

    QuickSort(participants, left, right);

    PrintParticipants(participants);
}