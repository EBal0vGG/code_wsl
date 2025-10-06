#include <bits/stdc++.h>
using namespace std;

string decode(const string &s) {
    stack<int> counts;
    stack<string> results;
    string current;

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (isdigit(c)) {
            counts.push(c - '0');
        } else if (c == '[') {
            results.push(current);
            current.clear();
        } else if (c == ']') {
            if (counts.empty() || results.empty()) {
                throw runtime_error("Некорректный формат строки");
            }
            int repeat = counts.top(); counts.pop();
            string prev = results.top(); results.pop();

            string tmp;
            for (int j = 0; j < repeat; j++) {
                tmp += current;
            }
            current = prev + tmp;
        } else {
            current.push_back(c);
        }
    }

    if (!counts.empty() || !results.empty()) {
        throw runtime_error("Некорректный формат строки");
    }

    return current;
}

int main() {
    string s;
    getline(cin, s);

    try {
        string res = decode(s);
        cout << res << endl;
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
