#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> parent;
vector<int> color; // 0 - не посещена, 1 - в обработке, 2 - обработана
int cycle_start = -1, cycle_end = -1;

bool dfs(int v, int par) {
    color[v] = 1;
    for (int u = 0; u < graph.size(); ++u) {
        if (graph[v][u] == 0) continue; // Нет ребра
        if (u == par) continue; // Пропускаем родителя
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u, parent[u])) {
                return true;
            }
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

vector<int> find_cycle(int n) {
    parent.assign(n, -1);
    color.assign(n, 0);
    cycle_start = -1;

    for (int v = 0; v < n; ++v) {
        if (color[v] == 0 && dfs(v, -1)) {
            break;
        }
    }

    if (cycle_start == -1) {
        return {};
    }

    vector<int> cycle;
    cycle.push_back(cycle_start + 1); // +1, т.к. вершины нумеруются с 1
    for (int v = cycle_end; v != cycle_start; v = parent[v]) {
        cycle.push_back(v + 1);
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

int main() {
    int n;
    cin >> n;

    graph.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    vector<int> cycle = find_cycle(n);

    if (cycle.empty()) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}