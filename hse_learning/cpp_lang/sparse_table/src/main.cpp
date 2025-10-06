#include <iostream>

#include "stb.hpp"

using namespace std;

int main() {
    int size;
    cout << "Введите размер вектора: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Введите элементы вектора: ";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    ST<int> st(arr); // Создаем sparse table

    int queryCount;
    std::cout << "Введите количество запросов: ";
    std::cin >> queryCount;

    for (int i = 0; i < queryCount; ++i) {
        int l, r;
        std::cout << "Введите границы запроса " << i + 1 << " (l и r): ";
        std::cin >> l >> r;

        if (l < 0 || r >= size || l > r) {
            std::cout << "Некорректные границы запроса!" << std::endl;
            continue;
        }

        std::cout << "Минимум на отрезке [" << l << ", " << r << "]: " << st.query(l, r) << std::endl;
    }

    return 0;
}