#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    double time;
    double value;
};

std::vector<Point> sumStepFunctions(const std::vector<Point> &f1, const std::vector<Point> &f2) {
    std::vector<Point> result;
    result.reserve(f1.size() + f2.size());
    
    auto it1 = f1.begin();
    auto it2 = f2.begin();
    double current_sum = 0.0;
    
    while (it1 != f1.end() || it2 != f2.end()) {
        double next_time;
        
        if (it1 == f1.end()) {
            next_time = it2->time;
        } else if (it2 == f2.end()) {
            next_time = it1->time;
        } else {
            next_time = std::min(it1->time, it2->time);
        }
        
        if (it1 != f1.end() && it1->time <= next_time) {
            current_sum += it1->value;
            ++it1;
        }
        if (it2 != f2.end() && it2->time <= next_time) {
            current_sum += it2->value;
            ++it2;
        }
        
        result.push_back({next_time, current_sum});
    }
    
    return result;
}

int main() {
    std::vector<Point> f1 = {{1.0, 2.0}, {3.0, 4.0}};
    std::vector<Point> f2 = {{2.0, 1.0}, {4.0, 3.0}};
    
    std::vector<Point> result = sumStepFunctions(f1, f2);
    
    for (const auto& m : result) {
        std::cout << "Time: " << m.time << ", Value: " << m.value << std::endl;
    }
    
    return 0;
}

