#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> constructAdj(vector<vector<int>> &edges, int V)
{
    vector<vector<vector<int>>> adj(V);
    for (const auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        adj[u].push_back({v,weight});
        adj[v].push_back({u,weight});
    }
    return adj;
}


vector<int> dijsktraAlgo(int V, vector<vector<int>> &edges, int src)
{
    vector<vector<vector<int>>> adj = constructAdj(edges, V);
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> result(V, INT_MAX);
    pq.push({0,src});
    result[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top()[1];
        pq.pop();
        for (auto neighbour : adj[u])
        {
            int v = neighbour[0];
            int weight = neighbour[1];
            if (result[v] > result[u] + weight)
            {
                result[v] = result[u] + weight;
                pq.push({result[v],v});
            }
        }
    }
    return result;
}

void printArray(vector<int> result)
{
    for (int i : result)
    {
        cout << i << " ";
    }
}

int main() {
    int V = 5;
    int src = 0;
    vector<vector<int>> edges = {{0,1,4}, {0,2,8},{1,4,6},{2,3,2}, {3,4,10}};
    vector<int> result = dijsktraAlgo(V, edges, src);
    printArray(result);
    return 0;
}
