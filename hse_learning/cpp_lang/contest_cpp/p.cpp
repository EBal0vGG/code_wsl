#include <iostream>
#include <string>

int main() {
    int x = 0, y = 0;
    std::string l;
    while (std::getline(std::cin, l)) {
        if (l.empty()) continue;
        size_t space = l.find(' ');
        std::string fst = l.substr(0, space);
        std::string snd = l.substr(space + 1);
        int steps = std::stoi(snd);
        if (fst == "North") {
            y += steps;
        } else if (fst == "South") {
            y -= steps;
        } else if (fst == "East") {
            x += steps;
        } else if (fst == "West") {
            x -= steps;
        }
    }
    std::cout << x << " " << y << std::endl;
    return 0;
}
