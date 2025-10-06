#include <iostream>
#include <string>

bool is_possible(const std::string &str) {
    int n = str.size();
    int left = 0, right = n - 1;
    bool move = false;
    
    while (left < right) {
        if (str[left] != str[right]) {
            if (!move) {
                left++;
                move = true;
            }
            else {
                break;
            }
        }
        else {
            left++, right--;
        }
    }
    if (left >= right) return true;

    left = 0, right = n - 1;
    move = false;
    while (left < right) {
        if (str[left] != str[right]) {
            if (!move) {
                right--;
                move = true;
            }
            else {
                return false;
            }
        }
        else {
            left++, right--;
        }
    }
    return true;
}

int main() {
    std::string str;
    
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);
    
    if (str.empty()) {
        std::cout << "Error: Empty string is not allowed" << std::endl;
        return 1;
    }
    
    std::cout << (is_possible(str) ? "true" : "false") << std::endl;
    
    std::string test_cases[] = {
        "aaab",    // true (remove 'b')
        "xyz",     // false
        "aababaa", // true (remove 'b')
        "abca",    // true (remove 'b' or 'c')
        "a",       // true (already palindrome)
        "aa",      // true (already palindrome)
        "ab",      // true (remove either 'a' or 'b')
    };
    
    std::cout << "\nTest cases:" << std::endl;
    for (const auto& test : test_cases) {
        std::cout << test << " -> " << (is_possible(test) ? "true" : "false") << std::endl;
    }

    return 0;
}