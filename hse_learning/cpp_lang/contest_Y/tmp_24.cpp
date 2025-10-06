#include <iostream>
#include <string>
#include <vector>
using namespace std;

int findPermutationSubstring(const string& T, const string& S) {
    if (S.empty() || T.empty() || S.length() > T.length()) {
        return -1;
    }
    
    // Create frequency arrays for S
    vector<int> sFreq(26, 0);
    for (char c : S) {
        sFreq[c - 'a']++;
    }
    
    // Create frequency array for current window
    vector<int> windowFreq(26, 0);
    int windowSize = S.length();
    
    // Initialize first window
    for (int i = 0; i < windowSize; i++) {
        windowFreq[T[i] - 'a']++;
    }
    
    // Check if first window matches
    if (windowFreq == sFreq) {
        return 0;
    }
    
    // Slide window and check each position
    for (int i = windowSize; i < T.length(); i++) {
        // Remove first character of previous window
        windowFreq[T[i - windowSize] - 'a']--;
        // Add last character of current window
        windowFreq[T[i] - 'a']++;
        
        if (windowFreq == sFreq) {
            return i - windowSize + 1;
        }
    }
    
    return -1;
}

int main() {
    string T, S;
    cin >> T >> S;
    
    cout << findPermutationSubstring(T, S) << endl;
    
    return 0;
}
