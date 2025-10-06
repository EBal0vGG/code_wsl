#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>

std::pair<int, int> get_array_i(std::vector<int> &vec, int X) {
    int n = vec.size();
    std::unordered_map<long, int> prefix_map;
    prefix_map[0] = 0;
    long long curr_sum = 0;
    
    for (int i = 0; i < n; i++) {
        curr_sum += vec[i];
        if (prefix_map.count(curr_sum - X)) {
            return {prefix_map[curr_sum - X], i + 1};
        }
        prefix_map[curr_sum] = i + 1;
    }
    
    return {0, 0};
}

int main() {

    int N, X;
    std::cin >> N;
    std::vector<int> vec(N);

    for (int i = 0; i < N; i++) {
        std::cin >> vec[i];
    }
    std::cin >> X;

    auto [fst, snd] = get_array_i(vec, X);

    std::cout << fst << " " << snd << std::endl;

    return 0;
}