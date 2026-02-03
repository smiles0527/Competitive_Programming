#include <bits/stdc++.h>
using namespace std;

// Consolidated header
#include <unordered_map>
#include <vector>

/**
 * @brief A simple undirected graph represented using an adjacency map.
 */
struct Graph {
  /**
   * @brief Constructs an empty graph.
   */
  Graph();

  /**
   * @brief Adds an undirected edge between vertices u and v.
   * @param u First vertex.
   * @param v Second vertex.
   */
  void add_edge(int u, int v);

  int num_vertices;
  std::unordered_map<int, std::vector<int>> adjacency_dict;
};

/**
 * @brief Finds all Hamiltonian paths in the graph.
 *
 * A Hamiltonian path visits each vertex exactly once.
 *
 * @param G The graph to search.
 * @return Vector of all Hamiltonian paths, where each path is a list of vertex indices.
 */
std::vector<std::vector<int>> find_hamiltonian_paths(Graph &G);

// Implementation
#include <functional>

Graph::Graph() { num_vertices = 0; }

void Graph::add_edge(int u, int v) {
    if (adjacency_dict.count(u) == 0) {
        adjacency_dict[u] = {};
    }

    if (adjacency_dict.count(v) == 0) {
        adjacency_dict[v] = {};
    }

    adjacency_dict[u].push_back(v);
    adjacency_dict[v].push_back(u);

    num_vertices = adjacency_dict.size();
}

std::vector<std::vector<int>> find_hamiltonian_paths(Graph &G) {
    std::vector<std::vector<int>> paths;
    std::function<void(int, std::vector<bool>, std::vector<int>&)> dfs;
    
    dfs = [&](int v, std::vector<bool> visited, std::vector<int> &path) {
        visited[v] = true;
        path.push_back(v);

        if (path.size() == G.num_vertices) {
            paths.push_back(path);
        } else {
            for (int w : G.adjacency_dict[v]) {
                if (!visited[w]) {
                    dfs(w, visited, path);
                }
            }
        }

        path.pop_back();
    };

    for (int start = 0; start < G.num_vertices; ++start) {
        std::vector<bool> visited(G.num_vertices, false);
        std::vector<int> path;
        dfs(start, visited, path);
    }

    return paths;
}
