#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;

    std::vector<unsigned int> Q(N);
    for (int i = 0; i < N; i++) {
        std::cin >> Q[i];
    }

    std::vector<unsigned char> C(N);
    for (int i = 0; i < N; i++) {
        int tmp;
        std::cin >> tmp;
        C[i] = static_cast<unsigned char>(tmp);
    }

    unsigned int A, B;
    std::cin >> A >> B;

    unsigned long long result = 0;
    for (int i = 0; i < N; i++) {
        unsigned int Di = A + ((C[i] + 1) * (B - A)) / 255;
        result += static_cast<unsigned long long>(Q[i]) * Di;
    }

    std::cout << result << std::endl;

    return 0;
}