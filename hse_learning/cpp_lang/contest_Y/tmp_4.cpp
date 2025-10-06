#include <iostream>
#include <vector>

std::vector<int> find_k_closest(const std::vector<int> &vec, int index, int k) {
    int target = vec[index];
    int n = vec.size();
    std::vector<int> result;
    
    int left = index - 1;
    int right = index + 1;
    
    result.push_back(target);
    k--;
    
    while (k > 0 && (left >= 0 || right < n)) {
        if (left >= 0 && right < n) {
            if (std::abs(vec[left] - target) <= std::abs(vec[right] - target)) {
                result.push_back(vec[left]);
                left--;
            } else {
                result.push_back(vec[right]);
                right++;
            }
        } else if (left >= 0) {
            result.push_back(vec[left]);
            left--;
        } else {
            result.push_back(vec[right]);
            right++;
        }
        k--;
    }
    
    return result;
}

int main() {
    // Example usage
    std::vector<int> arr = {4, 12, 15, 15, 30};
    int index = 1;
    int k = 3;
    
    std::vector<int> result = find_k_closest(arr, index, k);
    
    std::cout << "K closest elements to " << arr[index] << " are: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}