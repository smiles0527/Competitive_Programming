#include <bits/stdc++.h>
using namespace std;

// Graph minimal implementation for Bellman-Ford
template <class T> struct Vertex {
  Vertex(T value = T());
  Vertex(const Vertex<T> &vertex);
  T value;
  bool operator==(const Vertex<T> &other) const;
  bool operator!=(const Vertex<T> &other) const;
  bool operator<(const Vertex<T> &other) const;
};

template <class T> struct HashFunction {
  size_t operator()(const Vertex<T> &vertex) const;
};

template <class T> struct Edge {
  Edge(Vertex<T> source = Vertex<T>(), Vertex<T> destination = Vertex<T>(), int distance = 0);
  Vertex<T> source;
  Vertex<T> destination;
  int distance;
  bool operator<(const Edge<T> &other) const;
};

template <class T> class Graph {
  unordered_map<Vertex<T>, vector<Edge<T>>, HashFunction<T>> adjcDict;
public:
  Graph();
  void addEdge(Edge<T> edge);
  void addEdge(Vertex<T> source, Vertex<T> destination, int distance);
  vector<Vertex<T>> vertices() const;
  vector<Edge<T>> edgesFromVertex(const Vertex<T> vertex) const;
  vector<Edge<T>> edges() const;
  bool contains(const Vertex<T> vertex) const;
  unsigned int size() const;
  bool empty() const;
};

template <class T> Vertex<T>::Vertex(T _value) : value(_value) {}
template <class T> Vertex<T>::Vertex(const Vertex<T> &vertex) : value(vertex.value) {}
template <class T> bool Vertex<T>::operator==(const Vertex<T> &other) const { return value == other.value; }
template <class T> bool Vertex<T>::operator!=(const Vertex<T> &other) const { return value != other.value; }
template <class T> bool Vertex<T>::operator<(const Vertex<T> &other) const { return value < other.value; }
template <class T> size_t HashFunction<T>::operator()(const Vertex<T> &vertex) const { return hash<T>()(vertex.value); }
template <class T> Edge<T>::Edge(Vertex<T> _source, Vertex<T> _destination, int _distance) : source(_source), destination(_destination), distance(_distance) {}
template <class T> bool Edge<T>::operator<(const Edge<T> &other) const { return distance < other.distance; }
template <class T> Graph<T>::Graph() {}
template <class T> void Graph<T>::addEdge(Edge<T> edge) {
  if (contains(edge.source)) adjcDict[edge.source].emplace_back(edge);
  else adjcDict[edge.source] = vector<Edge<T>>{edge};
  if (!contains(edge.destination)) adjcDict[edge.destination] = vector<Edge<T>>{};
}
template <class T> void Graph<T>::addEdge(Vertex<T> source, Vertex<T> destination, int distance) {
  addEdge(Edge<T>(source, destination, distance));
}
template <class T> vector<Vertex<T>> Graph<T>::vertices() const {
  vector<Vertex<T>> result;
  for (const auto &[key, _] : adjcDict) result.emplace_back(key);
  return result;
}
template <class T> vector<Edge<T>> Graph<T>::edgesFromVertex(const Vertex<T> vertex) const {
  if (!contains(vertex)) throw invalid_argument("Graph<T> doesn't contain given vertex.");
  return adjcDict.at(vertex);
}
template <class T> vector<Edge<T>> Graph<T>::edges() const {
  vector<Edge<T>> result;
  for (auto [vertex, _edges] : adjcDict) copy(_edges.begin(), _edges.end(), back_inserter(result));
  return result;
}
template <class T> bool Graph<T>::contains(const Vertex<T> vertex) const {
  return adjcDict.find(vertex) != adjcDict.end();
}
template <class T> unsigned int Graph<T>::size() const { return adjcDict.size(); }
template <class T> bool Graph<T>::empty() const { return adjcDict.empty(); }

template class Vertex<int>;
template class Vertex<float>;
template class Vertex<double>;
template class Vertex<char>;
template class Edge<int>;
template class Edge<float>;
template class Edge<double>;
template class Edge<char>;
template class Graph<int>;
template class Graph<float>;
template class Graph<double>;
template class Graph<char>;

// Bellman-Ford algorithm
template <class T> int bellmanFord(const Graph<T> &graph, Vertex<T> source, Vertex<T> destination) {
  constexpr int INF = numeric_limits<int>::max();
  if (!graph.contains(source) || !graph.contains(destination)) return INF;
  if (source == destination) return 0;

  unordered_map<Vertex<T>, int, HashFunction<T>> distances;
  for (const auto &vertex : graph.vertices()) distances[vertex] = INF;
  distances[source] = 0;

  const auto allEdges = graph.edges();
  const size_t numVertices = graph.size();

  for (size_t i = 0; i < numVertices - 1; ++i) {
    bool updated = false;
    for (const auto &edge : allEdges) {
      if (distances[edge.source] != INF) {
        int newDistance = distances[edge.source] + edge.distance;
        if (newDistance < distances[edge.destination]) {
          distances[edge.destination] = newDistance;
          updated = true;
        }
      }
    }
    if (!updated) break;
  }

  for (const auto &edge : allEdges) {
    if (distances[edge.source] != INF && distances[edge.source] + edge.distance < distances[edge.destination]) {
      return INF;
    }
  }

  return distances[destination];
}

template int bellmanFord<int>(const Graph<int> &graph, Vertex<int> source, Vertex<int> destination);
template int bellmanFord<char>(const Graph<char> &graph, Vertex<char> source, Vertex<char> destination);
template int bellmanFord<float>(const Graph<float> &graph, Vertex<float> source, Vertex<float> destination);
template int bellmanFord<double>(const Graph<double> &graph, Vertex<double> source, Vertex<double> destination);
