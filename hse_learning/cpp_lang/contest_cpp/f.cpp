#include <iostream>

int main() {
    int n;
    std::cin >> n;

    std::string days[] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

    std::cout << days[n - 1] << std::endl;
    return 0;
}
