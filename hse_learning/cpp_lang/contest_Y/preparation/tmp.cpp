//=========//
// Номер 1 //
//=========//

/*
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_moves;
    cin >> num_moves;
    cin.ignore();

    unordered_map<string, int> move_from_counts;
    unordered_map<string, int> move_to_counts;

    for (int i = 0; i < num_moves; ++i) {
        string x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        string start_point = x1 + " " + y1;
        string end_point = x2 + " " + y2;

        move_from_counts[start_point]++;
        move_to_counts[end_point]++;
    }

    vector<string> path_starts;
    vector<string> path_ends;
    unordered_set<string> all_points;

    for (const auto& pair : move_from_counts) {
        all_points.insert(pair.first);
    }
    for (const auto& pair : move_to_counts) {
        all_points.insert(pair.first);
    }

    for (const string& point : all_points) {
        int outgoing = move_from_counts[point];
        int incoming = move_to_counts[point];

        if (outgoing - incoming == 1) {
            path_starts.push_back(point);
        } else if (incoming - outgoing == 1) {
            path_ends.push_back(point);
        } else if (outgoing != incoming) {
            cout << "-1\n";
            return 0;
        }
    }

    if (path_starts.size() == 1 && path_ends.size() == 1) {
        cout << path_starts[0] << " " << path_ends[0] << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}
*/

//=========//
// Номер 2 //
//=========//

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    int count[201] = {0};
    long long opportunities = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < p[i]; ++j) {
            opportunities += count[j];
        }
        count[p[i]]++;
    }

    cout << opportunities << endl;

    return 0;
}
*/

//=========//
// Номер 3 //
//=========//

/*
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Cell {
    int x, y;
    bool operator<(const Cell& other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
};

int main() {
    int W, H;
    cin >> W >> H;
    int N;
    cin >> N;

    vector<int> xL(N), yL(N), xR(N), yR(N);
    for (int i = 0; i < N; ++i) {
        cin >> xL[i] >> yL[i] >> xR[i] >> yR[i];
    }

    set<Cell> positions;
    for (int x = xL[0]; x <= xR[0]; ++x) {
        for (int y = yL[0]; y <= yR[0]; ++y) {
            positions.insert({x, y});
        }
    }

    for (int i = 1; i < N; ++i) {
        set<Cell> next_positions;

        for (auto [x, y] : positions) {
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};

            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 1 || nx > W || ny < 1 || ny > H) continue;

                if (nx >= xL[i] && nx <= xR[i] && ny >= yL[i] && ny <= yR[i]) {
                    next_positions.insert({nx, ny});
                }
            }
        }

        if (next_positions.empty()) {
            cout << "No" << endl;
            return 0;
        }

        positions = next_positions;
    }

    cout << "Yes" << endl;
}
*/