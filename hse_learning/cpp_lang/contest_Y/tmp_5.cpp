#include <iostream>
#include <limits>

int find_least_distance(const std::string &str) {
    int n = str.size();
    
    int min_distance = std::numeric_limits<int>::max();
    int last_x = -1, last_y = -1;
    
    for (int i = 0; i < n; i++) {
        if (str[i] == 'X') {
            last_x = i;
            if (last_y != -1) {
                min_distance = std::min(min_distance, std::abs(last_x - last_y));
            }
        }
        else if (str[i] == 'Y') {
            last_y = i;
            if (last_x != -1) {
                min_distance = std::min(min_distance, std::abs(last_x - last_y));
            }
        }
    }
    
    return min_distance == std::numeric_limits<int>::max() ? 0 : min_distance;
}

int main() {
    std::string str;
    std::cin >> str;
    
    int result = find_least_distance(str);
    std::cout << result << std::endl;
    
    return 0;
}