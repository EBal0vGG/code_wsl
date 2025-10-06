#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
    
    unordered_set<int> prefix_a;
    unordered_set<int> prefix_b;
    
    // For each prefix length K
    for (int K = 1; K <= N; K++) {
        // Add new elements to sets
        prefix_a.insert(a[K-1]);
        prefix_b.insert(b[K-1]);
        
        // Count common elements
        int common = 0;
        for (int x : prefix_b) {
            if (prefix_a.count(x) > 0) {
                common++;
            }
        }
        
        cout << common << " ";
    }
    cout << endl;
    
    return 0;
}
