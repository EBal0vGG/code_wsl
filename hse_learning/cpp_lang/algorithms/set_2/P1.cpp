#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int left;
    int right;

    size_t length();
    Interval overlap(const Interval& other);

    Interval(int left = 0, int right = 0) : left(left), right(right) {}
};

size_t Interval::length() {
    if (left >= right) return 0;
    return right - left + 1;
}

Interval Interval::overlap(const Interval& other) {
    if (right < other.left || left > other.right) {
        return Interval{0, -1};
    }
    
    int overlapLeft = (left < other.left) ? other.left : left;
    int overlapRight = (right > other.right) ? other.right : right;
    
    if (overlapLeft < overlapRight) {
        return Interval{overlapLeft, overlapRight};
    }
    return Interval{0, 0};
}

void insertion_sort(vector<Interval>& intervals, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Interval key = intervals[i];
        int j = i - 1;
        while (j >= left && key.left < intervals[j].left) {
            intervals[j + 1] = intervals[j];
            j--;
        }
        intervals[j + 1] = key;
    }
}

void merge_sort(vector<Interval>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    if (r - l <= 32) {
        insertion_sort(arr, l, r);
        return;
    }

    int mid = l + (r - l) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    
    if (arr[mid].left <= arr[mid + 1].left) {
        return;
    }
    
    vector<Interval> left_arr(arr.begin() + l, arr.begin() + mid + 1);
    vector<Interval> right_arr(arr.begin() + mid + 1, arr.begin() + r + 1);
    
    int i = 0, j = 0, k = l;
    
    while (i < left_arr.size() && j < right_arr.size()) {
        if (left_arr[i].left <= right_arr[j].left) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }
    
    while (i < left_arr.size()) {
        arr[k++] = left_arr[i++];
    }
    while (j < right_arr.size()) {
        arr[k++] = right_arr[j++];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        int left, right;
        cin >> left >> right;
    
        intervals[i] = Interval(left, right);
    }

    merge_sort(intervals, 0, n - 1);

    int max_right = intervals[0].right;
    int max_len = 0;
    Interval max_interval(0, -1);
    for (int i = 1; i < n; ++i) {
        if (intervals[i].left <= max_right) {
            int length = min(max_right, intervals[i].right)  - intervals[i].left + 1;
            if (length > max_len) {
                max_len = length;
                max_interval = Interval(intervals[i].left , min(max_right, intervals[i].right));
            }
        }
        
        if (intervals[i].right > max_right) {
            max_right = intervals[i].right;
        }
    }

    if (max_len > 0) {
        cout << max_len << endl;
        cout << max_interval.left << " " << max_interval.right << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
