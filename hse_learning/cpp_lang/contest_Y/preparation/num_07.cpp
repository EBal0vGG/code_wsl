#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> adj(N + 1); // Список смежности (вершины нумеруются с 1)
    
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Граф неориентированный
    }
    
    vector<bool> visited(N + 1, false);
    queue<int> q;
    vector<int> component;
    
    // Начинаем BFS с вершины 1
    q.push(1);
    visited[1] = true;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        component.push_back(current);
        
        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    // Сортируем вершины компоненты
    sort(component.begin(), component.end());
    
    // Выводим результат
    cout << component.size() << endl;
    for (int vertex : component) {
        cout << vertex << " ";
    }
    cout << endl;
    
    return 0;
}