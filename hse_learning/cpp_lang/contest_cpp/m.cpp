#include <iostream>
#include <cmath>

int main() {
    int n, a;
    std::cin >> n >> a;
    double sum = 0.0;
    do {
        sum += n * a;
        sum = sqrt(sum);
    } while (--n);
    std::cout << sum << std::endl;
    return 0;
}
