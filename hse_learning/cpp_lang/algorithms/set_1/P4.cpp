#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    stack<int> st;
    int need = 1;
    vector<pair<int,int>> ops;

    int pushCount = 0, popCount = 0;

    for (int x : arr) {
        st.push(x);
        pushCount++;

        while (!st.empty() && st.top() == need) {
            st.pop();
            popCount++;
            need++;
        }

        if (popCount > 0 && (st.empty() || st.top() != need)) {
            ops.push_back({1, pushCount});
            pushCount = 0;
            ops.push_back({2, popCount});
            popCount = 0;
        }
    }

    if (pushCount > 0) ops.push_back({1, pushCount});
    if (popCount > 0) ops.push_back({2, popCount});

    if (st.empty()) {
        for (auto [t, k] : ops) {
            cout << t << " " << k << endl;
        }
    } else {
        cout << 0 << endl;
    }

    return 0;
}
