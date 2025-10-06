#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct State {
    int cost;
    int coupons_left;
    int prev_coupons;
};

int main() {
    int N;
    cin >> N;
    vector<int> prices(N);
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];   
    }

    vector<vector<State>> dp(N + 1, vector<State>(N + 2, {INF, 0, 0}));
    dp[0][0] = {0, 0, 0};

    for (int day = 1; day <= N; ++day) {
        int price = prices[day - 1];
        for (int coupons = 0; coupons <= N; ++coupons) {
            // Option 1: Buy the lunch without using a coupon
            if (price <= 100) {
                if (dp[day - 1][coupons].cost + price < dp[day][coupons].cost) {
                    dp[day][coupons] = {dp[day - 1][coupons].cost + price, coupons, 0};
                }
            } else {
                if (dp[day - 1][coupons].cost + price < dp[day][coupons + 1].cost) {
                    dp[day][coupons + 1] = {dp[day - 1][coupons].cost + price, coupons, 0};
                }
            }

            // Option 2: Use a coupon (if available)
            if (coupons > 0) {
                if (dp[day - 1][coupons].cost < dp[day][coupons - 1].cost) {
                    dp[day][coupons - 1] = {dp[day - 1][coupons].cost, coupons, 1};
                }
            }
        }
    }

    // Find the minimal cost and the maximum number of remaining coupons
    int min_cost = INF;
    int best_k1 = 0;
    for (int coupons = 0; coupons <= N; ++coupons) {
        if (dp[N][coupons].cost <= min_cost) {
            if (dp[N][coupons].cost < min_cost || coupons > best_k1) {
                min_cost = dp[N][coupons].cost;
                best_k1 = coupons;
            }
        }
    }

    // Reconstruct the days when coupons were used
    vector<int> used_days;
    int current_coupons = best_k1;
    for (int day = N; day >= 1; --day) {
        if (dp[day][current_coupons].prev_coupons == 1) {
            used_days.push_back(day);
            current_coupons++;
        } else {
            if (prices[day - 1] > 100) {
                current_coupons--;
            }
        }
    }
    reverse(used_days.begin(), used_days.end());

    cout << min_cost << endl;
    cout << best_k1 << " " << used_days.size() << endl;
    for (int day : used_days) {
        cout << day << endl;
    }

    return 0;
}