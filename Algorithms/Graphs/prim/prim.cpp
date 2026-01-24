#include <bits/stdc++.h>
using namespace std;

// Graph for Prim
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
  bool operator>(const Edge<T> &other) const;
};

template <class T> class Graph {
  unordered_map<Vertex<T>, vector<Edge<T>>, HashFunction<T>> adjcDict;
public:
  Graph();
  void addEdge(Edge<T> edge);
  void addEdge(Vertex<T> source, Vertex<T> destination, int distance);
  vector<Vertex<T>> vertices() const;
  vector<Edge<T>> edgesFromVertex(const Vertex<T> vertex) const;
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
template <class T> bool Edge<T>::operator>(const Edge<T> &other) const { return distance > other.distance; }
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

// Prim's algorithm
template <class T> int prim(const Graph<T> &graph) {
  if (graph.empty()) return 0;
  auto vertices = graph.vertices();
  if (vertices.empty()) return 0;

  unordered_map<Vertex<T>, bool, HashFunction<T>> inMST;
  for (const auto &vertex : vertices) inMST[vertex] = false;

  Vertex<T> source = vertices.front();
  inMST[source] = true;

  auto cmp = [](const Edge<T> &a, const Edge<T> &b) { return a.distance > b.distance; };
  priority_queue<Edge<T>, vector<Edge<T>>, decltype(cmp)> minHeap(cmp);

  for (const auto &edge : graph.edgesFromVertex(source)) minHeap.push(edge);

  int mstWeight = 0;
  size_t verticesInMST = 1;
  const size_t totalVertices = vertices.size();

  while (!minHeap.empty() && verticesInMST < totalVertices) {
    Edge<T> minEdge = minHeap.top();
    minHeap.pop();
    const auto &v = minEdge.destination;
    if (inMST[v]) continue;
    inMST[v] = true;
    mstWeight += minEdge.distance;
    verticesInMST++;
    for (const auto &edge : graph.edgesFromVertex(v)) {
      if (!inMST[edge.destination]) minHeap.push(edge);
    }
  }
  return mstWeight;
}

template int prim<int>(const Graph<int> &graph);
template int prim<char>(const Graph<char> &graph);
template int prim<float>(const Graph<float> &graph);
template int prim<double>(const Graph<double> &graph);
