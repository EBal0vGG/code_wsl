#ifndef QSORT_H
#define QSORT_H

#include <vector>

int partition(std::vector<int> &arr, int low, int high);

void quickSort(std::vector<int> &arr, int low, int high);

void SortFunction(std::vector<int> &arr);

#endif // QSORT_H