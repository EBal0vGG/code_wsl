#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
 
struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        size_t seed = v.size();
        for (int x : v) {
            seed ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};
 
int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
 
    int max_hamming = 0;
    std::unordered_set<std::vector<int>, VectorHash> unique_rotations;
 
    for (int rotation = 1; rotation < n; ++rotation) {
        int diff_pos = 0;
        for (int i = 0; i < n; ++i) {
            if (vec[i] != vec[(i + rotation) % n]) {
                diff_pos++;
            }
        }
 
        if (diff_pos > max_hamming) {
            max_hamming = diff_pos;
            unique_rotations.clear();
        }
 
        if (diff_pos == max_hamming) {
            std::vector<int> rotated(n);
            for (int i = 0; i < n; ++i) {
                rotated[i] = vec[(i + rotation) % n];
            }
            unique_rotations.insert(std::move(rotated));
        }
    }
    if (max_hamming == 0) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << unique_rotations.size() << std::endl;
    }
    return 0;
}