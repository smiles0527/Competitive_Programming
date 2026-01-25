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
 * @brief Finds all valid k-colorable configurations of the graph.
 *
 * A k-colorable configuration assigns one of k colors to each vertex
 * such that no two adjacent vertices share the same color.
 *
 * @param G The graph to color.
 * @param k The number of available colors.
 * @return Vector of all valid configurations.
 */
std::vector<std::vector<int>> find_k_colorable_configurations(Graph &G, int k);

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
  if (adjacency_dict.size() > num_vertices) {
    num_vertices = adjacency_dict.size();
  }
}

std::vector<std::vector<int>> find_k_colorable_configurations(Graph &G, int k) {
  std::vector<std::vector<int>> configurations;

  std::function<bool(Graph &, int, int, std::vector<int> &)> is_colorable;
  is_colorable = [&](Graph &G, int v, int color, std::vector<int> &colors) {
    for (int u : G.adjacency_dict[v]) {
      if (colors[u] == color) {
        return false;
      }
    }
    return true;
  };

  std::function<void(Graph &, int, std::vector<int> &, std::vector<int> &)> dfs;
  dfs = [&](Graph &G, int v, std::vector<int> &colors,
            std::vector<int> &configuration) {
    if (v == G.num_vertices) {
      configurations.push_back(configuration);
      return;
    }

    for (int color = 0; color < k; ++color) {
      if (is_colorable(G, v, color, colors)) {
        colors[v] = color;
        configuration.push_back(color);
        dfs(G, v + 1, colors, configuration);
        configuration.pop_back();
        colors[v] = -1;
      }
    }
  };

  auto colors = std::vector<int>(G.num_vertices, -1);
  auto configuration = std::vector<int>();
  dfs(G, 0, colors, configuration);
  return configurations;
}
