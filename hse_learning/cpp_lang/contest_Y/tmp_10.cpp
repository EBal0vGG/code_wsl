#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Solution 1: Using boolean array (O(N + M) time, O(M) space)
string compressRange(const vector<int>& nums) {
    if (nums.empty()) return "";
    
    // Find maximum number to determine array size
    int maxNum = *max_element(nums.begin(), nums.end());
    
    // Create boolean array to mark present numbers
    vector<bool> present(maxNum + 1, false);
    
    // Mark all present numbers
    for (int num : nums) {
        present[num] = true;
    }
    
    string result;
    bool first = true;
    
    // Scan through the boolean array to find ranges
    for (int i = 0; i <= maxNum; i++) {
        if (!present[i]) continue;
        
        // Find the end of current range
        int j = i;
        while (j <= maxNum && present[j]) j++;
        
        // Add to result
        if (!first) result += ",";
        first = false;
        
        if (j - i == 1) {
            result += to_string(i);
        } else {
            result += to_string(i) + "-" + to_string(j - 1);
        }
        
        i = j - 1; // Skip to end of current range
    }
    
    return result;
}

// Solution 2: Using sorting (O(N log N) time, O(1) extra space)
string compressRangeSort(vector<int> nums) {
    if (nums.empty()) return "";
    
    // Sort the array
    sort(nums.begin(), nums.end());
    
    string result;
    bool first = true;
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (!first) result += ",";
        first = false;
        
        int start = nums[i];
        // Find the end of current range
        while (i + 1 < nums.size() && nums[i + 1] == nums[i] + 1) {
            i++;
        }
        
        if (nums[i] == start) {
            result += to_string(start);
        } else {
            result += to_string(start) + "-" + to_string(nums[i]);
        }
    }
    
    return result;
}

int main() {
    // Test cases
    vector<vector<int>> testCases = {
        {1,4,5,2,3,9,8,11,0},
        {1,4,3,2},
        {1,4},
        {1,2}
    };
    
    cout << "Testing boolean array solution:\n";
    for (const auto& nums : testCases) {
        cout << "Input: [";
        for (size_t i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size() - 1) cout << ",";
        }
        cout << "]\nOutput: " << compressRange(nums) << "\n\n";
    }
    
    cout << "\nTesting sorting solution:\n";
    for (const auto& nums : testCases) {
        cout << "Input: [";
        for (size_t i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size() - 1) cout << ",";
        }
        cout << "]\nOutput: " << compressRangeSort(nums) << "\n\n";
    }
    
    return 0;
}
