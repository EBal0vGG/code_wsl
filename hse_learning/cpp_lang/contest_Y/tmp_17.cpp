#include <iostream>
#include <string>

std::string& multiply(std::string &str, int n) {
    int carry = 0;
    for (int i = 0; i < str.size(); i++) {
        int res = (str[i] - '0') * n;
        str[i] = (res + carry) % 10 + '0';
        carry = (res + carry) / 10;
    }
    if (carry) str.push_back(carry + '0');
    return str;
}

int main() {
    std::string s = "012";
    std::cout << multiply(s, 9) << std::endl;

    return 0;
}