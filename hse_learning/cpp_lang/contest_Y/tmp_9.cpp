#include <string>
#include <iostream>

void replaceSpaces(std::string& str) {
    // Count spaces
    int spaceCount = 0;
    for (char c : str) {
        if (c == ' ') spaceCount++;
    }
    
    // Calculate new length
    int oldLength = str.length();
    int newLength = oldLength + spaceCount * 2;  // Each space becomes "%20" (3 chars)
    
    // Resize string to accommodate new length
    str.resize(newLength);
    
    // Fill from the end
    int j = newLength - 1;
    for (int i = oldLength - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[j] = '0';
            str[j-1] = '2';
            str[j-2] = '%';
            j -= 3;
        } else {
            str[j] = str[i];
            j--;
        }
    }
}

int main() {
    std::string str = "Hello World  ";
    replaceSpaces(str);
    std::cout << str << std::endl;
    return 0;
}
