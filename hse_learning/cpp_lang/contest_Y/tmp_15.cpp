#include <string>
#include <iostream>

bool fuzzySearch(const std::string& pattern, const std::string& text) {
    if (pattern.empty()) return true;
    if (text.empty()) return false;
    
    size_t patternIndex = 0;
    
    for (size_t i = 0; i < text.length() && patternIndex < pattern.length(); ++i) {
        if (tolower(text[i]) == tolower(pattern[patternIndex])) {
            patternIndex++;
        }
    }
    
    return patternIndex == pattern.length();
}

int main() {
    // Test cases from the example
    std::cout << "fuzzysearch('car', 'cartwheel'): " << (fuzzySearch("car", "cartwheel") ? "true" : "false") << std::endl;
    std::cout << "fuzzysearch('cwhl', 'cartwheel'): " << (fuzzySearch("cwhl", "cartwheel") ? "true" : "false") << std::endl;
    std::cout << "fuzzysearch('cwhee', 'cartwheel'): " << (fuzzySearch("cwhee", "cartwheel") ? "true" : "false") << std::endl;
    std::cout << "fuzzysearch('cartwheel', 'cartwheel'): " << (fuzzySearch("cartwheel", "cartwheel") ? "true" : "false") << std::endl;
    std::cout << "fuzzysearch('cwheeel', 'cartwheel'): " << (fuzzySearch("cwheeel", "cartwheel") ? "true" : "false") << std::endl;
    std::cout << "fuzzysearch('lw', 'cartwheel'): " << (fuzzySearch("lw", "cartwheel") ? "true" : "false") << std::endl;
    
    return 0;
}
