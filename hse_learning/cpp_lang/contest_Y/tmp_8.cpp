#include <iostream>
#include <string>
#include <regex>

std::string removeSmileys(const std::string& text) {
    std::regex smileyPattern(":-\\(+|:-\\)+");
    return std::regex_replace(text, smileyPattern, "");
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << removeSmileys(line) << std::endl;
    }
    return 0;
}
