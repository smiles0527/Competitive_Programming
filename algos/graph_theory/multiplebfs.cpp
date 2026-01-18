#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> bfsMultiple(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<vector<int>> all;

    for (int start = 0; start < V; start++) {
        if (!visited[start]) {
            queue<int> q;
            vector<int> comp;
            visited[start] = true;
            q.push(start);

            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                comp.push_back(curr);

                for (int x : adj[curr]) {
                    if (!visited[x]) {
                        visited[x] = true;
                        q.push(x);
                    }
                }
            }

            all.push_back(comp);
        }
    }

    return all;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    vector<vector<int>> edges = {{0, 1}, {0, 2}, {3, 4}};
    for (auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<vector<int>> res = bfsMultiple(adj);

    for (auto &comp : res) {
        for (int v : comp) cout << v << " ";
        cout << '\n';
    }
}
