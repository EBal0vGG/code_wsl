#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
};

void insertion_sort(vector<int>& arr, Stats& st) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            st.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                st.swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void shell_sort(vector<int>& arr, Stats& st) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap) {
                st.comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    st.swaps++;
                    j -= gap;
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

vector<int> generate_array(int n, int max = 1000) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % max;
    }
    return arr;
}

void run_test(int n) {
    vector<int> arr1 = generate_array(n);
    vector<int> arr2 = arr1;

    Stats stats_insertion, stats_shell;

    insertion_sort(arr1, stats_insertion);
    shell_sort(arr2, stats_shell);

    cout << "\n=== Тест для массива размера " << n << " ===\n";

    cout << "Сортировка вставками:\n";
    cout << "  Сравнения:    " << stats_insertion.comparisons << "\n";
    cout << "  Перестановки: " << stats_insertion.swaps << "\n";

    cout << "Сортировка Шелла:\n";
    cout << "  Сравнения:    " << stats_shell.comparisons << "\n";
    cout << "  Перестановки: " << stats_shell.swaps << "\n";

    cout << "\nРазница (Вставки - Шелл):\n";
    cout << "  Сравнения:    " 
         << (stats_insertion.comparisons - stats_shell.comparisons) << "\n";
    cout << "  Перестановки: " 
         << (stats_insertion.swaps - stats_shell.swaps) << "\n";
}

int main() {
    srand(time(0));

    cout << "Сравнительный анализ сортировок\n";

    run_test(10);
    run_test(100);
    run_test(1000);
    run_test(10000);
    run_test(50000);

    return 0;
}