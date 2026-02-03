#include <bits/stdc++.h>
using namespace std;

// Graph and A* minimal implementation
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
  bool operator==(const Edge<T> &other) const;
  bool operator!=(const Edge<T> &other) const;
  bool operator<(const Edge<T> &other) const;
};

template <class T> class Graph {
  unordered_map<Vertex<T>, vector<Edge<T>>, HashFunction<T>> adjcDict;
public:
  Graph();
  Graph(unordered_map<Vertex<T>, vector<Edge<T>>, HashFunction<T>> adjcDict);
  void addEdge(Edge<T> edge);
  void addEdge(Vertex<T> source, Vertex<T> destination, int distance);
  void addVertex(Vertex<T> vertex);
  vector<Vertex<T>> vertices() const;
  vector<Edge<T>> edgesFromVertex(const Vertex<T> vertex) const;
  vector<Edge<T>> edges() const;
  bool contains(const Vertex<T> vertex) const;
  bool connected(const Vertex<T> source, const Vertex<T> destination) const;
  bool empty() const;
  unsigned int size() const;
};

template <class T> Vertex<T>::Vertex(T _value) : value(_value) {}
template <class T> Vertex<T>::Vertex(const Vertex<T> &vertex) : value(vertex.value) {}
template <class T> bool Vertex<T>::operator==(const Vertex<T> &other) const { return value == other.value; }
template <class T> bool Vertex<T>::operator!=(const Vertex<T> &other) const { return value != other.value; }
template <class T> bool Vertex<T>::operator<(const Vertex<T> &other) const { return value < other.value; }
template <class T> size_t HashFunction<T>::operator()(const Vertex<T> &vertex) const { return hash<T>()(vertex.value); }

template <class T> Edge<T>::Edge(Vertex<T> _source, Vertex<T> _destination, int _distance)
    : source(_source), destination(_destination), distance(_distance) {}
template <class T> bool Edge<T>::operator==(const Edge<T> &other) const {
  return source == other.source && destination == other.destination && distance == other.distance;
}
template <class T> bool Edge<T>::operator!=(const Edge<T> &other) const {
  return source != other.source || destination != other.destination || distance != other.distance;
}
template <class T> bool Edge<T>::operator<(const Edge<T> &other) const { return distance < other.distance; }

template <class T> Graph<T>::Graph() {}
template <class T> Graph<T>::Graph(unordered_map<Vertex<T>, vector<Edge<T>>, HashFunction<T>> adjcDict) : adjcDict(adjcDict) {}
template <class T> void Graph<T>::addEdge(Edge<T> edge) {
  auto source = edge.source, destination = edge.destination;
  if (contains(source)) adjcDict[source].emplace_back(edge);
  else adjcDict[source] = vector<Edge<T>>{edge};
  if (!contains(destination)) adjcDict[destination] = vector<Edge<T>>{};
}
template <class T> void Graph<T>::addEdge(Vertex<T> source, Vertex<T> destination, int distance) {
  addEdge(Edge<T>(source, destination, distance));
}
template <class T> void Graph<T>::addVertex(Vertex<T> vertex) {
  if (!contains(vertex)) adjcDict[vertex] = vector<Edge<T>>{};
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
template <class T> bool Graph<T>::connected(const Vertex<T> source, const Vertex<T> destination) const {
  if (!contains(source) || !contains(destination)) return false;
  for (auto &edge : adjcDict.at(source)) if (edge.destination == destination) return true;
  return false;
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

// A* algorithm
template <class T> int aStar(const Graph<T> &graph, Vertex<T> source, Vertex<T> destination, double (*heuristic)(T a, T b)) {
  constexpr int INF = numeric_limits<int>::max();
  if (!graph.contains(source) || !graph.contains(destination)) return INF;
  if (source == destination) return 0;

  unordered_map<Vertex<T>, int, HashFunction<T>> gScore;
  unordered_map<Vertex<T>, double, HashFunction<T>> fScore;
  for (const auto &vertex : graph.vertices()) {
    gScore[vertex] = INF;
    fScore[vertex] = numeric_limits<double>::max();
  }
  gScore[source] = 0;
  fScore[source] = heuristic(source.value, destination.value);

  auto cmp = [&](const Vertex<T> &l, const Vertex<T> &r) { return fScore[l] > fScore[r]; };
  priority_queue<Vertex<T>, vector<Vertex<T>>, decltype(cmp)> openSet(cmp);
  unordered_map<Vertex<T>, bool, HashFunction<T>> inOpenSet;
  openSet.push(source);
  inOpenSet[source] = true;

  while (!openSet.empty()) {
    Vertex<T> current = openSet.top();
    openSet.pop();
    inOpenSet[current] = false;
    if (current == destination) return gScore[destination];

    for (const auto &edge : graph.edgesFromVertex(current)) {
      const auto &neighbor = edge.destination;
      int tentativeGScore = gScore[current] + edge.distance;
      if (tentativeGScore < gScore[neighbor]) {
        gScore[neighbor] = tentativeGScore;
        fScore[neighbor] = tentativeGScore + heuristic(neighbor.value, destination.value);
        if (!inOpenSet[neighbor]) {
          openSet.push(neighbor);
          inOpenSet[neighbor] = true;
        }
      }
    }
  }
  return gScore[destination] < INF ? gScore[destination] : INF;
}

// Point structure for A* (if needed)
struct Point { double x, y; };
template int aStar<Point>(const Graph<Point> &graph, Vertex<Point> source, Vertex<Point> destination, double (*heuristic)(Point a, Point b));
