#include <vector>
#include <iostream>
#include <algorithm>

int findMaxDistance(const std::vector<int> &seats) {
    int n = seats.size();
    int dist_left = 0;
    int mx_dist = 0;

    for (int i = 0; i < n; i++) {
        if (seats[i] == 1) {
            mx_dist = std::max(mx_dist, dist_left / 2 + (dist_left % 2));
            dist_left = 0;
        }
        if (seats[i] == 0) {
            dist_left++;
        }
    }

    auto first_one_it = std::find(seats.begin(), seats.end(), 1);
    int first_one = (first_one_it != seats.end()) ? std::distance(seats.begin(), first_one_it) : -1;

    auto last_one_it = std::find(seats.rbegin(), seats.rend(), 1);
    int last_one = (last_one_it != seats.rend()) ? std::distance(seats.rbegin(), last_one_it) : -1;

    mx_dist = std::max(mx_dist, first_one);
    mx_dist = std::max(mx_dist, last_one);
    return mx_dist;
}

int main() {
    std::vector<int> seats = {0, 1, 0, 1, 0, 0, 0, 1, 0};

    std::cout << "Max distance: " << findMaxDistance(seats) << std::endl;
    return 0;
}
