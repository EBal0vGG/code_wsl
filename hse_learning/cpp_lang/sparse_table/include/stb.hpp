#ifndef STCLASS_H
#define STCLASS_H

#include <vector>
#include <climits>
#include <cmath>

// Sparse Table
template <typename Type>
class ST {
private:
    std::vector<std::vector<Type>> st; // Хранит предвычисленные результаты
    Type n;                            // Размер исходного массива

public:
    // Конструктор принимает массив и строит таблицу
    ST(const std::vector<Type>& arr) : n(arr.size()) {
        int maxLog = std::log2(n) + 1;

        // Инициализируем таблицу размером n x maxLog
        st.resize(n, std::vector<Type>(maxLog));

        // Заполняем первый столбец значениями из исходного массива
        for (int i = 0; i < n; ++i)
            st[i][0] = arr[i];

        // Заполнение остальных столбцов
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                // Операция для вычисления значений в таблице
                // Здесь используем std::min() для поиска минимума на отрезках
                st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Декструктор по умолчанию
    ~ST() = default;

    // Функция для получения минимального элемента на отрезке [L, R]
    Type query(int L, int R) const {
        if (L > R || L < 0 || R >= n) return INT_MAX; // Проверка корректности индексов

        int length = R - L + 1;
        int k = std::log2(length);

        // Используем предвычисленные значения из таблицы
        return std::min(st[L][k], st[R - (1 << k) + 1][k]);
    }
};

#endif