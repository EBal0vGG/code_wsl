#include <iostream>
#include <algorithm>
#include <vector>

void fill_dp(std::vector<std::vector<int>> &dp, std::vector<int> &x, std::vector<int> &y) {
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            if (x[i] == y[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else {
                dp[i + 1][j + 1] = std::max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
}

void fill_LCS(std::vector<int> &lcs,
              std::vector<int> &x,
              std::vector<int> &y,
              std::vector<std::vector<int>> &dp)
{
    int i = dp.size() - 1, j = dp[0].size() - 1;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            lcs.push_back(x[i - 1]);
            i--;
            j--;
        }
        else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }
        }
    }
    std::reverse(lcs.begin(), lcs.end());
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int> x(N);
    for (int i = 0; i < N; i++) {
        std::cin >> x[i];
    }
    int M;
    std::cin >> M;
    std::vector<int> y(M);
    for (int i = 0; i < M; i++) {
        std::cin >> y[i];
    }

    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));
    fill_dp(dp, x, y);

    std::vector<int> lcs;
    fill_LCS(lcs, x, y, dp);

    for (int a : lcs) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    return 0;
}