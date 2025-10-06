#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<int>> dist(n, vector<int>(m, numeric_limits<int>::max()));
    queue<pair<int, int>> q;
    string tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        for (int j = 0; j < m; j++) {
            if (tmp[j] == 'x') {
                dist[i][j] = 0;
                q.emplace(i, j);
            }
        }
    }

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int ni = i + "2011"[k] - '1';
            int nj = j + "1102"[k] - '1';
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && dist[ni][nj] == numeric_limits<int>::max()) {
                dist[ni][nj] = dist[i][j] + 1;
                q.emplace(ni, nj);
            }
        }
    }

    vector<vector<int>> dp(n, vector<int>(m));
    int mx_ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[i][j] >= d) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
                mx_ans = max(mx_ans, dp[i][j]);
            }
        }
    }
    cout << mx_ans << endl;
    return 0;
}
