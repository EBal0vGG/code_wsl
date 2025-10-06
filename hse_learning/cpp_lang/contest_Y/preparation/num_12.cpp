#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> graph[i][j];
        }
    }

    int start, end;
    cin >> start >> end;
    start--;
    end--;

    if (start == end) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> distance(N, -1);
    queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < N; ++neighbor) {
            if (graph[current][neighbor] == 1 && distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;

                if (neighbor == end) {
                    cout << distance[neighbor] << endl;
                    return 0;
                }

                q.push(neighbor);
            }
        }
    }

    cout << -1 << endl;

    return 0;
}