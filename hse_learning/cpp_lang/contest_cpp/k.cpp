#include <iostream>
#include <cmath>

int main() {
    int k;
    double a, b;
    std::cin >> k >> a >> b;
    switch (k) {
        case 0:
            std::cout << a + b << std::endl;
            break;
        case 1:
            std::cout << a - b << std::endl;
            break;
        case 2:
            std::cout << a * b << std::endl;
            break;
        case 3:
            std::cout << a / b << std::endl;
            break;
        case 4:
            std::cout << pow(a, b) << std::endl;
            break;
        case 5:
            std::cout << pow(b, 1.0 / a) << std::endl;
            break;
        default:
            std::cout << -1 << std::endl;
    }
    return 0;
}
