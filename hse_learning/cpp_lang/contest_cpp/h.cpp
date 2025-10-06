#include <iostream>

int main() {
    int N, K, M;
    std::cin >> N >> K >> M;
    int D = 0;
    if (K < M) {
        std::cout << 0 << std::endl;
        return 0;
    }
    int material = N;
    while (material >= K) {
        int form = material / K;
        int after_form = material % K;
        int D_part = (K / M) * form;
        int material_after_D = (K % M) * form;
        D += D_part;
        material = after_form + material_after_D;
    }
    std::cout << D << std::endl;
    return 0;
}
