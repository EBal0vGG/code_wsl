#include <vector>
#include <unordered_map>

std::vector<int> FilterSortedList(const std::vector<int>& first, const std::vector<int>& second) {
    std::unordered_map<int, bool> second_elements;
    std::vector<int> result;
    
    // Create a map of elements from the second sequence
    for (int num : second) {
        second_elements[num] = true;
    }
    
    // Check each element from the first sequence
    for (int num : first) {
        if (second_elements.find(num) == second_elements.end()) {
            result.push_back(num);
        }
    }
    
    return result;
}
