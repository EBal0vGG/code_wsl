#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

vector<string> digitToLetters = {
    "",     // 0
    "",     // 1
    "ABC",  // 2
    "DEF",  // 3
    "GHI",  // 4
    "JKL",  // 5
    "MNO",  // 6
    "PQRS", // 7
    "TUV",  // 8
    "WXYZ"  // 9
};

string encodeWord(const string& word) {
    string encoded;
    for (char c : word) {
        c = toupper(c);
        for (int digit = 2; digit <= 9; ++digit) {
            if (digitToLetters[digit].find(c) != string::npos) {
                int count = digitToLetters[digit].find(c) + 1;
                encoded += string(count, '0' + digit);
                break;
            }
        }
    }
    return encoded;
}

string decodeMessage(const string& s, const unordered_map<string, string>& encodedDictionary) {
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; ++i) {
        if (!dp[i]) continue;
        for (const auto& pair : encodedDictionary) {
            const string& encodedWord = pair.first;
            if (s.substr(i, encodedWord.length()) == encodedWord) {
                dp[i + encodedWord.length()] = true;
            }
        }
    }

    string result;
    int i = n;
    while (i > 0) {
        for (const auto& pair : encodedDictionary) {
            const string& encodedWord = pair.first;
            const string& word = pair.second;
            if (i >= encodedWord.length() && dp[i - encodedWord.length()] &&
                s.substr(i - encodedWord.length(), encodedWord.length()) == encodedWord) {
                result = word + " " + result;
                i -= encodedWord.length();
                break;
            }
        }
    }

    return result;
}

int main() {
    string s;
    cin >> s;

    int n;
    cin >> n;
    unordered_map<string, string> encodedDictionary;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        string encodedWord = encodeWord(word);
        encodedDictionary[encodedWord] = word;
    }

    string result = decodeMessage(s, encodedDictionary);

    cout << result << endl;

    return 0;
}