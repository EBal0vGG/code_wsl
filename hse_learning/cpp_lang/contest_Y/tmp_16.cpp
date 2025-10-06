#include <iostream>
#include <vector>
#include <algorithm>

void del_zeroes(std::vector<int> &vec) {
    int n = vec.size();
    int non_zero_index = 0;
    int non_zero_count = 0;
    for (int i = 0; i < n; i++) {
        if (vec[i] == 0) {
            non_zero_index = std::max(non_zero_index, i + 1);
            for (; non_zero_index < n && vec[non_zero_index] == 0; non_zero_index++)
                ;
            if (non_zero_index < n) {
                vec[i] = vec[non_zero_index];
                vec[non_zero_index] = 0;
            }
        }
        if (vec[i] != 0) {
            non_zero_count++;
        }
    }
    vec.resize(non_zero_count);
}

void del_zeroes_std(std::vector<int> &vec) {
    vec.erase(
        std::remove(vec.begin(), vec.end(), 0),
        vec.end()
    );
}

int main() {
    std::vector<int> a = {1, 2, 0, 3, 4, 0, 0, 0, 5, 6};
    std::vector<int> b = a;  // Create a copy for the second solution
    
    std::cout << "Original solution: ";
    del_zeroes(a);
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "STL solution: ";
    del_zeroes_std(b);
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}