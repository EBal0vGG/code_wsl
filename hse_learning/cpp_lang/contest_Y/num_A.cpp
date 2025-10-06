#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // n - этажи
    // m - квартиры
    // x - высота y - ширина в квартире
    int n, m, x, y;
    std::cin >> n >> m >> x >> y;

    std::vector<std::string> windows(n * x);
    for (int i = 0; i < n * x; i++) {
        std::cin >> windows[i];
    }

    int ans = 0;

    for (int floor = 0; floor < n; floor++) {
        for (int k = 0; k < m; k++) {
            int light = 0;

            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    if (windows[floor * x + i][k * y + j] == 'X') {
                        light++;
                    }
                }
            }

            if (light >= std::ceil((x * y) / 2.0)) {
                ans++;
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}