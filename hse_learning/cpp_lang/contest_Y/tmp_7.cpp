#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countPairsWithDiff(vector<int>& nums, int k) {
    if (nums.empty()) return 0;
    
    // Sort the array
    sort(nums.begin(), nums.end());
    
    int count = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        int target = nums[i] + k;
        auto it = lower_bound(nums.begin() + i + 1, nums.end(), target);
        
        count += nums.end() - it;
    }
    
    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << countPairsWithDiff(nums, k) << endl;
    
    return 0;
}
