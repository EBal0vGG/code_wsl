#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

bool isVertSym(const vector<pair<int, int>>& points) {
    if (points.empty()) return true;
    if (points.size() == 1) return true;
    
    // Find min and max x coordinates
    int minX = points[0].first, maxX = points[0].first;
    for (const auto& p : points) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
    }
    
    // Try potential symmetry lines
    // The line must be at a position where points can be paired
    set<int> potentialLines;
    for (const auto& p1 : points) {
        for (const auto& p2 : points) {
            if (p1 != p2) {
                // If points have same y-coordinate, their midpoint is a potential line
                if (p1.second == p2.second) {
                    potentialLines.insert(p1.first + p2.first);
                }
            }
        }
    }
    
    // If no potential lines found, check if all points are on the same vertical line
    if (potentialLines.empty()) {
        return minX == maxX;
    }
    
    // Try each potential line
    for (int x : potentialLines) {
        map<pair<int, int>, int> leftPoints;
        map<pair<int, int>, int> rightPoints;
        
        // Count points on the line
        int onLine = 0;
        
        // Distribute points to left and right
        for (const auto& p : points) {
            if (p.first == x) {
                onLine++;
            } else if (p.first < x) {
                leftPoints[p]++;
            } else {
                rightPoints[p]++;
            }
        }
        
        // Check if remaining points can be paired symmetrically
        bool possible = true;
        for (const auto& p : leftPoints) {
            pair<int, int> symPoint = {2 * x - p.first.first, p.first.second};
            if (rightPoints[symPoint] != p.second) {
                possible = false;
                break;
            }
        }
        
        // Check if all right points have been paired
        for (const auto& p : rightPoints) {
            pair<int, int> symPoint = {2 * x - p.first.first, p.first.second};
            if (leftPoints[symPoint] != p.second) {
                possible = false;
                break;
            }
        }
        
        if (possible) return true;
    }
    
    return false;
}

int main() {
    // Test cases
    vector<pair<int, int>> test1 = {{0, 0}, {0, 1}, {1, 1}, {2, 2}, {3, 1}, {4, 1}, {4, 0}};
    vector<pair<int, int>> test2 = {{0, 0}, {0, 0}, {1, 1}, {2, 2}, {3, 1}, {4, 0}, {4, 0}};
    vector<pair<int, int>> test3 = {{0, 0}, {0, 0}, {1, 1}, {2, 2}, {3, 1}, {4, 0}};
    vector<pair<int, int>> test4 = {};
    vector<pair<int, int>> test5 = {{0, 0}};
    vector<pair<int, int>> test6 = {{0, 0}, {10, 0}};
    vector<pair<int, int>> test7 = {{0, 0}, {11, 1}};
    vector<pair<int, int>> test8 = {{0, 0}, {1, 0}, {3, 0}};
    
    cout << "Test 1: " << isVertSym(test1) << endl;  // true
    cout << "Test 2: " << isVertSym(test2) << endl;  // true
    cout << "Test 3: " << isVertSym(test3) << endl;  // false
    cout << "Test 4: " << isVertSym(test4) << endl;  // true
    cout << "Test 5: " << isVertSym(test5) << endl;  // true
    cout << "Test 6: " << isVertSym(test6) << endl;  // true
    cout << "Test 7: " << isVertSym(test7) << endl;  // false
    cout << "Test 8: " << isVertSym(test8) << endl;  // false
    
    return 0;
}
