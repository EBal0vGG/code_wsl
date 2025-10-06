#include <iostream>

int main() {
    int v, t;
    std::cin >> v >> t;

    if (v > 0) {
        std::cout << (v * t) % 109 << std::endl;
    } else {
        std::cout << (109 - (-v * t) % 109) % 109 << std::endl;
    }
    
    return 0;
}
