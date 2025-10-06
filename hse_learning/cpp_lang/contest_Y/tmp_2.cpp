#include <iostream>
#include <vector>
#include <utility>

int get_max_len(std::vector<int> &vec) {
    int more_len = 1;
    int less_len = 1;

    int ans = 1;

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[i - 1]) {
            more_len++;
            less_len = 1;
            ans = std::max(more_len, ans);
        }
        if (vec[i] < vec[i - 1]) {
            less_len++;
            more_len = 1;
            ans = std::max(less_len, ans);
        }
    }
    return ans;
}

int main() {

    int N;
    std::cin >> N;
    std::vector<int> vec(N);

    for (int i = 0; i < N; i++) {
        std::cin >> vec[i];
    }

    std::cout << get_max_len(vec) << std::endl;

    return 0;
}