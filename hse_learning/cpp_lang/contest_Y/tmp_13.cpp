#include <string>
#include <algorithm>
#include <iostream>

std::string sum(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        
        if (i >= 0) {
            sum += (a[i] >= 'a' ? a[i] - 'a' + 10 : a[i] - '0');
            i--;
        }
        
        if (j >= 0) {
            sum += (b[j] >= 'a' ? b[j] - 'a' + 10 : b[j] - '0');
            j--;
        }
        
        carry = sum / 16;
        sum %= 16;
        
        char digit = (sum < 10) ? '0' + sum : 'a' + (sum - 10);
        result.push_back(digit);
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    // Example usage:
    std::string result = sum("fed", "13"); // result will be "1000"
    std::cout << result << std::endl;
    return 0;
}