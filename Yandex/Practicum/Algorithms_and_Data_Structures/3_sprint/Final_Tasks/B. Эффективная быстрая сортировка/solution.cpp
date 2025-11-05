/*
    https://contest.yandex.ru/contest/23815/run-report/147414276/
*/

/*
    -- ПРИНЦИП РАБОТЫ --
    Инвариант: закрытый интервал [left, right]. На каждом уровне вычисляем pivot = participants[left + (rand() % (right - left + 1))]
    и работаем с его копией выбранного из [left, right], на каждом рекурсивном вызове работаем на отрезке [left, right], который обновляется. 
    Базовый случай рекурсии left >= right

    На каждом уровне инициализируем i = left, j = right до входа в бесконечный цикл, в первом внутреннем цикле сначала сдвигаем ++i указатель до тех пор, пока participants[i] < pivot &&
    compare_participants(participants[i], pivot) - true, также во втором внутреннем цикле двигаем --j указатель до тех пор, пока pivot < participants[j] &&
    compare_participants(pivot, participants[j]) - true. Если i >= j — разбиение завершено и выходим из бесконечного цикла, иначе std::swap(participants[i], participants[j]), 
    затем ++i, --j.
    Сортировка проходит так: (-left.solved_tasks_, left.fine_, left.login_) < (-right.solved_tasks_, right.fine_, right.login_)

    Продолжаю идти дальше рекурсивно, взяв такие диапазоны: 
    partition_in_place(participants, left, j);
    partition_in_place(participants, j + 1, right);
    до тех пор пока не достигну базового случая рекурсии if (left >= right) return;

    Далее выводим login_ каждого элемента отсортированного массива

    -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
    Из принципа работы понятно, что сортировка проходит на месте и в диапазоне [left, right] на каждом этапе рекурсии, сортируя правильно элементы
    засчет компаратора: (-left.solved_tasks_, left.fine_, left.login_) < (-right.solved_tasks_, right.fine_, right.login_).

    Также учтен базовый случай рекурсии, дабы не допустить бесконечного цикла, всегда выхожу из рекурсии, когда left указатель находится дальше, 
    чем right указатель на длине массива: if (left >= right) return;

    После каждой итерации получается [left, j] < pivot, [j + 1, right] > pivot. Всегда останавливаюсь когда i >= j. 

    -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    Пусть S - participants.size(), тогда на каждом уровне мы пробегаемся указателями i и j по 
    подмассивам уровня - O(S), также глубина рекурсии в среднем случае O(log S), в худшем при неудачном 
    pivot O(S)
    Итог: O(S * log S); Worse: O(S^2)

    -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    Пусть N - participants.size()
    Дополнительные данные, которые использую pivot, i, left, j, right
    Также заполняется стек через рекурсию, при удачном pivot будет log N, в худшем N
    Итог: O(1) + O(log N); Worse: O(1) + O(N)
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Participant {
    Participant() : login_(""), solved_tasks_(0), fine_(0) {
    }

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
        Memory Complexity: O(log N); Worse: O(N)
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