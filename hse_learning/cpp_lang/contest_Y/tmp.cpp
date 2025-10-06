#include <iostream>
#include <vector>
#include <cassert>

int maxOnes(const std::vector<int>& nums) {
    int cnt_1 = 0, cnt_2 = 0;
    int ans = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            ans = std::max(ans, cnt_1 + cnt_2);
            cnt_1 = cnt_2;
            cnt_2 = 0;
        }
        if (nums[i] == 1) {
            cnt_2++;
        }
    }
    ans = std::max(ans, cnt_1 + cnt_2);

    return ans;
}

int main() {
    assert(maxOnes({0, 0}) == 0);
    assert(maxOnes({1, 0}) == 1);
    assert(maxOnes({0, 1}) == 1);
    assert(maxOnes({1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1}) == 5);
    assert(maxOnes({1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}) == 6);
    assert(maxOnes({1, 1, 1, 1, 0, 0}) == 4);
    assert(maxOnes({1, 1, 1, 1}) == 4);
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
