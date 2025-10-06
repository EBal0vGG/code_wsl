#include <string>
#include <iostream>

std::string normalize(const std::string& s) {
    std::string result = s;
    if (result.empty()) return result;
    
    int write_pos = 0;
    bool prev_space = false;
    
    for (int read_pos = 0; read_pos < result.length(); ++read_pos) {
        if (result[read_pos] != ' ' || !prev_space) {
            result[write_pos++] = result[read_pos];
        }
        prev_space = (result[read_pos] == ' ');
    }
    
    result.resize(write_pos);
    return result;
}

int main() {
    std::string test = "some   string   ";
    std::cout << normalize(test) << std::endl;
    return 0;
}
