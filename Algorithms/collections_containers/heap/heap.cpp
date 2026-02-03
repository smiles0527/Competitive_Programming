#include <bits/stdc++.h>

using namespace std;

template <class T> class Heap {

public:
  Heap(function<bool(T, T)> comp);
  Heap(const Heap &other);
  Heap &operator=(const Heap &other);

  void push(const T &val);
  T pop();
  const T &peek() const;
  unsigned int size() const;
  bool empty() const;
  void clear();
  bool isMaxHeap() const;
  bool isMinHeap() const;

private:
  vector<T> data;
  function<bool(const T &, const T &)> comp;

  int parentIdx(int index) const;
  int leftNodeIdx(int index) const;
  int rightNodeIdx(int index) const;
};

template <class T> class MinHeap : public Heap<T> {
public:
  MinHeap();
};

template <class T> class MaxHeap : public Heap<T> {
public:
  MaxHeap();
};

template <class T>
Heap<T>::Heap(function<bool(T, T)> comp) : comp(comp) {}

template <class T>
Heap<T>::Heap(const Heap &other) : data(other.data), comp(other.comp) {}

template <class T> Heap<T> &Heap<T>::operator=(const Heap &other) {
  if (this != &other) {
    data = other.data;
    comp = other.comp;
  }
  return *this;
}

template <class T> void Heap<T>::push(const T &val) {
  data.push_back(val);
  int index = static_cast<int>(data.size()) - 1;
  int parent = parentIdx(index);

  // Bubble up
  while (index > 0 && comp(data[index], data[parent])) {
    swap(data[index], data[parent]);
    index = parent;
    parent = parentIdx(index);
  }
}

template <class T> T Heap<T>::pop() {
  if (data.empty()) {
    throw out_of_range("Heap is empty");
  }

  T val = data[0];
  data[0] = data.back();
  data.pop_back();

  if (!data.empty()) {
    // Bubble down
    int index = 0;
    int size = static_cast<int>(data.size());

    while (true) {
      int left = leftNodeIdx(index);
      int right = rightNodeIdx(index);
      int smallest = index;

      if (left < size && comp(data[left], data[smallest])) {
        smallest = left;
      }
      if (right < size && comp(data[right], data[smallest])) {
        smallest = right;
      }

      if (smallest == index) {
        break;
      }

      swap(data[index], data[smallest]);
      index = smallest;
    }
  }

  return val;
}

template <class T> const T &Heap<T>::peek() const {
  if (data.empty()) {
    throw out_of_range("Heap is empty");
  }
  return data[0];
}

template <class T> unsigned int Heap<T>::size() const {
  return static_cast<unsigned int>(data.size());
}

template <class T> bool Heap<T>::empty() const { return data.empty(); }

template <class T> void Heap<T>::clear() { data.clear(); }

template <class T> bool Heap<T>::isMaxHeap() const { return comp(2, 1); }

template <class T> bool Heap<T>::isMinHeap() const { return comp(1, 2); }

template <class T> int Heap<T>::parentIdx(int index) const {
  return (index - 1) / 2;
}

template <class T> int Heap<T>::leftNodeIdx(int index) const {
  return 2 * index + 1;
}

template <class T> int Heap<T>::rightNodeIdx(int index) const {
  return 2 * index + 2;
}

template <class T> MinHeap<T>::MinHeap() : Heap<T>(less<T>()) {}

template <class T> MaxHeap<T>::MaxHeap() : Heap<T>(greater<T>()) {}

template class Heap<int>;
template class Heap<float>;
template class Heap<double>;
template class Heap<char>;

template class MinHeap<int>;
template class MinHeap<float>;
template class MinHeap<double>;
template class MinHeap<char>;

template class MaxHeap<int>;
template class MaxHeap<float>;
template class MaxHeap<double>;
template class MaxHeap<char>;
