#include <iostream>
#include <cmath>

int main() {
    int a, b;
    std::cin >> a >> b;
    double c = std::sqrt(a * a + b * b);
    printf("%.6f\n", c);
    return 0;
}
