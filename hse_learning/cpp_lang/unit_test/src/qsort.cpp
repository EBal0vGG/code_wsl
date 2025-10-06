#include <iostream>
#include <vector>

#include "../include/qsort.hpp"

int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[high]; // Опорный элемент
    int i = (low - 1); // Индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high); // Разделяем массив вокруг опорного элемента

        // Рекурсивная сортировка левой и правой частей
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Функция для вызова Quick Sort
void SortFunction(std::vector<int> &arr) {
    quickSort(arr, 0, arr.size() - 1);
}
