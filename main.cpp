#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <random>
#include <set>

using namespace std;

#define RANGE(container) container.begin(), container.end()

template <typename T>
ostream& operator << (ostream& out, vector<T> a){
    bool comma = false;

    for(auto el : a)
        if(comma) out << ", " << el;
            else {comma = true; out << "[" << el;}

    return out << "]\n";
}

int main() {
/* --- 1)Создайте последовательность П1 целых чисел от 1 до 10 --- */
    vector<int> p1(10);
    iota(RANGE(p1), 1);

/* --- 2)Добавьте еще несколько чисел в конец П1 из cin --- */
    int n = 3;
    while(n--)
        *back_inserter(p1) = *istream_iterator<int>(cin);

/* --- 3)Перемешайте П1 случайным образом--- */
    auto current_timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
    auto generator = std::mt19937_64(current_timestamp);

    std::shuffle(p1.begin(), p1.end(), generator);

/* --- 4)Удалите дубликаты из П1 --- */
    {
        set<int> check_unique;
        vector<int> unique;
        unique.reserve(p1.size());

        for_each(RANGE(p1), [&unique, &check_unique](auto elem) {
            if (check_unique.insert(elem).second) unique.push_back(elem); //записывает, если элемент был добавлен в set
        });
        p1 = move(unique);
    }

/* --- 5)Подсчитайте количество нечетных чисел в П1 --- */
    {
        int k = count_if(RANGE(p1), [](auto elem){return (elem % 2 == 1);});
        cout << "Quantity of odd numbers in p1: " << k << endl;
    }


/* --- 6)Определите минимальное и максимальное значения в П1 --- */
    {
        int min = *min_element(RANGE(p1));
        int max = *max_element(RANGE(p1));
        cout << "In p1 min: " << min << ", max: " << max << endl;
    }

/* --- 7)Попробуйте найти хотя бы одно простое число в П1 --- */
    {
        set<int> Prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
                                  89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                                  181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                                  281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
                                  397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
                                  503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
                                  619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
                                  743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
                                  863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

        auto it = find_if(RANGE(p1), [&Prime_numbers](auto elem){return Prime_numbers.count(elem);});
        if(it != p1.end()) cout << "Prime number in p1:" << *it << endl;
            else cout << "Where no prime numbers less than 1000" << endl;
    }

/* --- 8)Замените все числа в П1 их квадратами --- */
    {
        vector<int> squared;
        std::transform(RANGE(p1), std::back_inserter(squared), [](auto elem){return elem * elem;});

        p1 = move(squared);
    }

/* --- 9)Создайте последовательность П2 из N случайных чисел, где N - длина П1 --- */
    vector<int> p2;
    p2.reserve(p1.size());
    {
        int A = 1, B = 100;
        auto distribution = uniform_int_distribution(A, B);

        std::generate_n(std::back_inserter(p2), p1.size(),
                        [&distribution, &generator]() {
                            return distribution(generator);
                        });
    }

/* --- 10)Вычислите сумму чисел в П2 --- */
    int sum_p2 = accumulate(RANGE(p2), 0);
    cout << "Sum of p2 elements: " << sum_p2 << endl;

/* --- 11)Замените первые несколько чисел в П2 числом 1 --- */
    {
        int change_position = uniform_int_distribution<>(0, p2.size()-1)(generator);

        replace_if(p2.begin(), next(p2.begin(), change_position), [](auto) {return true;}, 1);
    }

/* --- 12)Создайте последовательность ПЗ как разность П1 и П2 --- */
    vector<int> p3;
    transform(RANGE(p1), p2.begin(), back_inserter(p3), [](auto from_1, auto from_2){return from_1+from_2;});

/* --- 13)Заменить каждый отрицательный элемент в ПЗ нулем --- */
    replace_if(RANGE(p3), [](auto elem) {return (elem < 0);}, 0);

/* --- 14)Удалите полностью все нулевые элементы из ПЗ --- */
    remove(RANGE(p3), 0);

/* --- 15)Измените порядок следования элементов в ПЗ на обратный --- */
    reverse(RANGE(p3));

/* --- 16)Определите быстро топ-3 наибольших элемента в ПЗ --- */
    nth_element(p3.begin(), next(p3.begin(), 2), p3.end(), greater<>());
    cout << "top 3 (in p3): "; copy(p3.begin(), next(p3.begin(),3), ostream_iterator<int>(cout, " ")); cout << endl;

/* --- 17)Отсортируйте полностью П1 и П2 по возрастанию --- */
    sort(RANGE(p1));
    sort(RANGE(p2));

/* --- 18)Создайте последовательность П4 как слияние П1 и П2 --- */
    vector<int> p4;
    merge(RANGE(p1),RANGE(p2), back_inserter(p4));

/* --- 19)Определите диапазон для упорядоченной вставки числа 1 в П4 --- */
    auto range = equal_range(RANGE(p4), 1);

/* --- 20)Выведите все последовательности в cout --- */
    cout << "p1: " << p1;
    cout << "p2: " << p2;
    cout << "p3: " << p3;
    cout << "p4: " << p4;
    return 0;
}

