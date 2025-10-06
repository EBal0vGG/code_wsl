#include <iostream>
#include <string>
#include <vector>
using namespace std;

int solve(const string& s) {
    int n = s.length();
    vector<int> last_pos(128, -1);  // Для ASCII символов
    long long result = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        // Если текущий символ уже встречался в текущем окне
        if (last_pos[s[right]] >= left) {
            left = last_pos[s[right]] + 1;
        }
        last_pos[s[right]] = right;
        // Добавляем количество новых валидных пар
        result += right - left + 1;
    }
    
    return result;
}

int main() {
    string s;
    cin >> s;
    cout << solve(s) << endl;
    return 0;
}
