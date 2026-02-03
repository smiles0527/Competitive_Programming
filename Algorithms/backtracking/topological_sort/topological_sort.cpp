#include <bits/stdc++.h>
using namespace std;

// Consolidated header
#include <stack>
#include <vector>

/**
 * @brief A directed graph for topological sorting.
 */
class Graph {
public:
  /**
   * @brief Constructs a graph with n vertices.
   * @param n Number of vertices.
   */
  Graph(int n);

  /**
   * @brief Adds a directed edge from u to v.
   * @param u Source vertex.
   * @param v Destination vertex.
   */
  void add_edge(int u, int v);

  /**
   * @brief Performs topological sort on the graph.
   * @return A vector of vertices in topological order.
   */
  std::vector<int> topological_sort();

private:
  int num_vertices;
  std::vector<std::vector<int>> adjacency_list;
  void topological_sort_util(int v, std::vector<bool> &visited,
                             std::stack<int> &Stack);
};

// Implementation

Graph::Graph(int V) : num_vertices(V) {
    adjacency_list.resize(V);
}

void Graph::add_edge(int u, int v) {
    adjacency_list[u].push_back(v);
}

void Graph::topological_sort_util(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
    visited[v] = true;
    for (int i : adjacency_list[v])
        if (!visited[i])
            topological_sort_util(i, visited, Stack);
    Stack.push(v);
}

std::vector<int> Graph::topological_sort() {
    std::stack<int> Stack;
    std::vector<bool> visited(num_vertices, false);

    for (int i = 0; i < num_vertices; i++)
        if (!visited[i])
            topological_sort_util(i, visited, Stack);

    std::vector<int> result;
    while (!Stack.empty()) {
        result.push_back(Stack.top());
        Stack.pop();
    }
    return result;
}
