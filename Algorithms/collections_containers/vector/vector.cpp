#include <bits/stdc++.h>

using namespace std;

template <class T> class Vector {

public:
  Vector();
  Vector(const Vector<T> &v);
  ~Vector();

  typedef T *iterator;
  typedef const T *const_iterator;
  
  int size() const;
  int capacity() const;
  bool empty() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;
  void push_back(const T &value);
  void pop_back();

  void resize(unsigned int size);
  void reserve(unsigned int capacity);
  T &operator[](unsigned int index);
  const T &operator[](unsigned int index) const;
  T &at(unsigned int index);
  const T &at(unsigned int index) const;
  Vector<T> &operator=(const Vector<T> &);
  void clear();

private:
  int n;
  int _capacity;
  T *data;
};

template <class T> Vector<T>::Vector() : _capacity(0), n(0), data(nullptr) {}

template <class T> Vector<T>::Vector(const Vector<T> &v) {
  n = v.n;
  _capacity = v._capacity;
  if (_capacity > 0) {
    data = new T[_capacity];
    for (int i = 0; i < n; i++) {
      data[i] = v.data[i];
    }
  } else {
    data = nullptr;
  }
}

template <class T> Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  if (this != &v) {
    delete[] data;
    n = v.n;
    _capacity = v._capacity;
    if (_capacity > 0) {
      data = new T[_capacity];
      for (int i = 0; i < n; i++) {
        data[i] = v.data[i];
      }
    } else {
      data = nullptr;
    }
  }
  return *this;
}

template <class T> Vector<T>::~Vector() { delete[] data; }

template <class T> typename Vector<T>::iterator Vector<T>::begin() {
  return data;
}

template <class T> typename Vector<T>::iterator Vector<T>::end() {
  return data + n;
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return data;
}

template <class T> typename Vector<T>::const_iterator Vector<T>::end() const {
  return data + n;
}

template <class T> T &Vector<T>::front() {
  if (n == 0)
    throw out_of_range("Vector is empty");
  return data[0];
}

template <class T> const T &Vector<T>::front() const {
  if (n == 0)
    throw out_of_range("Vector is empty");
  return data[0];
}

template <class T> T &Vector<T>::back() {
  if (n == 0)
    throw out_of_range("Vector is empty");
  return data[n - 1];
}

template <class T> const T &Vector<T>::back() const {
  if (n == 0)
    throw out_of_range("Vector is empty");
  return data[n - 1];
}

template <class T> void Vector<T>::push_back(const T &v) {
  if (n >= _capacity) {
    // Double capacity (or start with 1 if empty)
    reserve(_capacity == 0 ? 1 : _capacity * 2);
  }
  data[n++] = v;
}

template <class T> bool Vector<T>::empty() const { return n == 0; }

template <class T> void Vector<T>::pop_back() {
  if (n == 0)
    throw out_of_range("Vector is empty");
  --n;
}

template <class T> void Vector<T>::reserve(unsigned int newCapacity) {
  if (static_cast<int>(newCapacity) <= _capacity) {
    return;
  }

  T *newData = new T[newCapacity];
  for (int i = 0; i < n; i++) {
    newData[i] = data[i];
  }

  delete[] data;
  data = newData;
  _capacity = static_cast<int>(newCapacity);
}

template <class T> int Vector<T>::size() const { return n; }

template <class T> int Vector<T>::capacity() const { return _capacity; }

template <class T> void Vector<T>::resize(unsigned int newSize) {
  if (static_cast<int>(newSize) > _capacity) {
    reserve(newSize);
  }
  n = static_cast<int>(newSize);
}

template <class T> T &Vector<T>::operator[](unsigned int index) {
  if (index >= static_cast<unsigned int>(n))
    throw out_of_range("Index out of range");
  return data[index];
}

template <class T> const T &Vector<T>::operator[](unsigned int index) const {
  if (index >= static_cast<unsigned int>(n))
    throw out_of_range("Index out of range");
  return data[index];
}

template <class T> T &Vector<T>::at(unsigned int index) {
  if (index >= static_cast<unsigned int>(n))
    throw out_of_range("Index out of range");
  return data[index];
}

template <class T> const T &Vector<T>::at(unsigned int index) const {
  if (index >= static_cast<unsigned int>(n))
    throw out_of_range("Index out of range");
  return data[index];
}

template <class T> void Vector<T>::clear() {
  n = 0;
}

template class Vector<int>;
template class Vector<float>;
template class Vector<double>;
template class Vector<char>;
