#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm> // для std::sort

#include "../include/qsort.hpp"

// Функция для сравнения двух массивов
bool arraysEqual(const std::vector<int> &a, const std::vector<int> &b) {
    return a == b;
}

// Тестовый класс для всех тестов сортировки
class SortTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Тест на пустом массиве
TEST_F(SortTest, EmptyArray) {
    std::vector<int> input = {};
    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, {}));
}

// Тест на одном элементе
TEST_F(SortTest, OneElement) {
    std::vector<int> input = {42};
    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, {42}));
}

// Тест на нескольких одинаковых элементах
TEST_F(SortTest, AllSameElements) {
    std::vector<int> input = {7, 7, 7, 7};
    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, {7, 7, 7, 7}));
}

// Тест на упорядоченном массиве
TEST_F(SortTest, AlreadySorted) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, {1, 2, 3, 4, 5}));
}

// Тест на обратном порядке
TEST_F(SortTest, ReverseOrder) {
    std::vector<int> input = {5, 4, 3, 2, 1};
    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, {1, 2, 3, 4, 5}));
}

// Тест на случайном наборе чисел
TEST_F(SortTest, RandomNumbers) {
    // Создаем генератор случайных чисел
    std::mt19937 generator(std::random_device{}()); // Инициализируем генератор случайным устройством
    std::uniform_int_distribution<int> distribution(0, 99); // Устанавливаем диапазон чисел

    // Создаем вектор для хранения случайных чисел
    std::vector<int> input(10000);
    std::vector<int> expected(10000);

    // Заполняем вектор случайными числами
    int i = 0;
    for (int& number : input) {
        number = distribution(generator);
        expected[i++] = number;
    }
    std::sort(expected.begin(), expected.end());

    SortFunction(input);
    EXPECT_TRUE(arraysEqual(input, expected));
}