#include <iostream>
#include <vector>

struct Point {
    int value;
    int count;
};

int DotProduct(std::vector<Point> &vec_1, std::vector<Point> &vec_2) {
    int dot_pr = 0;
    int j = 0;
    int sz = vec_1.size();
    for (int i = 0; i < sz; i++) {
        int cnt_1 = vec_1[i].count;
        int cnt_2 = vec_2[j].count;
        while (cnt_1 > 0) {
            dot_pr += vec_1[i].value * vec_2[j].value;
            cnt_1--;
            if (--cnt_2 == 0) {
                j++;
                cnt_2 = vec_2[j].count;
            }
        }
    }
    return dot_pr;
}

int main() {
    std::vector<Point> a = {Point{1, 3}};
    std::vector<Point> b = {Point{1, 2}, Point{10, 1}};
    std::cout << DotProduct(a, b) << std::endl;

    return 0;
}