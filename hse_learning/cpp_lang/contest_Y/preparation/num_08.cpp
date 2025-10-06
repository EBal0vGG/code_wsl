#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, component);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1); // Нумерация вершин с 1

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Граф неориентированный
    }

    vector<bool> visited(N + 1, false);
    vector<int> component;

    vector<vector<int>> ans;
    for (int i = 1; i < N + 1; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, component); // Запускаем DFS из вершины 1
            sort(component.begin(), component.end()); // Сортируем вершины
            ans.push_back(component);
            component.clear();
        }
    }

    cout << ans.size() << endl;
    for (vector<int> v : ans) {
        cout << v.size() << endl;
        for (int node : v) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}