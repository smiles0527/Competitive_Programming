#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> adjArr(vector<vector<int>> edges, int V){
    vector<vector<vector<int>>> adj (V);
    for (const auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    return adj;
}

vector<int> dijkstraAlgo(vector<vector<int>> edges, int V, int src){

    vector<vector<vector<int>>> adj = adjArr(edges, V);
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> result(V, INT_MAX);
    pq.push({0, src});
    result[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top()[1];
        pq.pop();
        for (const auto neighbour : adj[u])
        {
            int v = neighbour[0];
            int weight = neighbour[1];
            if (result[v] > result[u] + weight)
            {
                result[v] = result[u] + weight;
                pq.push({result[v], v});
            }
        }
    }
    return result;
}

void printArr(vector<int> result){
    for (int i : result){
        cout << i << " ";
    }
}
int main(){
    // adjacency array, u, v, weight
    vector<vector<int>> edges = {{0,1,4}, {0,2,8},{1,4,6},{2,3,2}, {3,4,10}};
    int src = 0;
    vector<int> result = dijkstraAlgo(edges, edges.size(), src);
    printArr(result);
}
