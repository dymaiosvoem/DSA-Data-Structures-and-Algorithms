/*
    https://contest.yandex.ru/contest/23815/run-report/147406571/
*/

/*
    -- ПРИНЦИП РАБОТЫ --
    Я реализовал сломанный поиск бинарным способом. Инвариант: искомый элемент k, если он существует, то принадлежит полуоткрытому интервалу [left, right).
    Первым шагом обозначаю левый индекс массива (left = 0), правый индекс массива (right = vec.size()), далее беру элемент массива из 
    середины (mid = left + (right - left) / 2) и провожу операцию сравнения с нужным мне значением (vec[mid] == k, при выполнении 
    такого условия возвращается индекс mid, как индекс k в массиве), если условие не выполняется, приступаю к сравнению, чтобы понять 
    с какой стороны массив отсортирован по возрастанию и проверяю, находится ли k в отсортированном интервале.

    Если отсортировано слева vec[left] <= k && k < vec[mid], то ищем в этом интервале, иначе смещаем левый указатель на left = mid + 1
    Если отсортировано справа vec[mid] < k && k <= vec[right - 1], то ищем в этом интервале, иначе смещаем правый указатель right = mid
    Цикл работает пока left < right, поэтому при обращении к vec[right - 1] индекс валиден

    В конце проверяю, находится ли left указатель в массиве vec или нет left < vec.size() && vec[left] == k ? left : -1
 
    -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
    Из принципа работы понятно, что если k существует в массиве, то при каждой итерации k принадлежит [left, right)
    Если vec[left] <= k && k < vec[mid], то k лежит в отсортированной левой половине, делаем right = mid, иначе left = mid + 1
    Если vec[mid] < k && k <= vec[right - 1], то k лежит в отсортированной правой половине, делаем left = mid + 1, иначе right = mid
    При каждой итерации длина массива уменьшается. 
    В результате проверяем, входит ли лувый указатель в целую длину массива или нет left < vec.size() && vec[left] == k ? left : -1

    -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    Пусть размер массива - N, на каждом шаге мы делим массив пополам, пытаясь найти k. 
    Итог: O(log N)

    -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    Дополнительные данные которые использую - константы left, mid, right. 
    Итог: O(1)
*/

#include <cassert>
#include <vector>

int broken_search(const std::vector<int>& vec, int k) {
    /*
        Time Complexity: O(log N)
        Memory Complexity: O(1)
    */
    int left = 0, right = vec.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == k) {
            return mid;
        }

        if (vec[left] <= vec[mid]) {
            if (vec[left] <= k && k < vec[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        } else {
            if (vec[mid] < k && k <= vec[right - 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
    }

    return (left < vec.size() && vec[left] == k ? left : -1);
}

void test() {
    std::vector<int> bad = { 3, 4, 5, 6, 7, 0, 1, 2 };
    assert(7 == broken_search(bad, 2));

    std::vector<int> arr = { 19, 21, 100, 101, 1, 3, 4, 5, 7, 12 };
    assert(7 == broken_search(arr, 5));

    std::vector<int> arr_2 = { 5, 1 };
    assert(1 == broken_search(arr_2, 1));

    std::vector<int> arr_3 = { 1, 3, 4, 5, 7, 12, 19, 21, 100, 101 };
    assert(3 == broken_search(arr_3, 5));

    std::vector<int> arr_4 = { 19, 21, 100, 101, 1, 4, 5, 7, 12 };
    assert(6 == broken_search(arr_4, 5));

    std::vector<int> arr_5 = { 1 };
    assert(0 == broken_search(arr_5, 1));

    std::vector<int> arr_6 = { 4, 5, 6, 7, 0, 1, 2, 3 };
    assert(2 == broken_search(arr_6, 6));
}

int main() {
    test();
}