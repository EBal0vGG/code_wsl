#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int sign = 1;
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += sign * (1.0 / i);
        sign = -sign;
    }
    
    std::cout << sum << std::endl;
    
    return 0;
}