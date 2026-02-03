#include <bits/stdc++.h>

using namespace std;

template <class T> class LinkedList {

public:
  LinkedList();
  LinkedList(const LinkedList<T> &l);
  LinkedList<T> &operator=(const LinkedList<T> &l);
  ~LinkedList();

  void push_back(const T &v);
  void push_front(const T &v);
  void pop_back();
  void pop_front();
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;
  bool empty() const;
  void clear();
  int size() const;
  void remove(const T &v);
  bool contains(const T &v) const;

private:
  struct Node {
    T data;
    unique_ptr<Node> next;
  };

  unique_ptr<Node> head;
  Node *tail;
  int n;
};

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), n(0) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &l)
    : head(nullptr), tail(nullptr), n(0) {
  const Node *p = l.head.get();
  while (p != nullptr) {
    push_back(p->data);
    p = p->next.get();
  }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &l) {
  if (this != &l) {
    clear();
    const Node *p = l.head.get();
    while (p != nullptr) {
      push_back(p->data);
      p = p->next.get();
    }
  }
  return *this;
}

template <class T> LinkedList<T>::~LinkedList() { clear(); }

template <class T> void LinkedList<T>::push_back(const T &v) {
  auto newNode = make_unique<Node>();
  newNode->data = v;
  
  if (empty()) {
    tail = newNode.get();
    head = move(newNode);
  } else {
    tail->next = move(newNode);
    tail = tail->next.get();
  }
  n++;
}

template <class T> void LinkedList<T>::push_front(const T &v) {
  auto newNode = make_unique<Node>();
  newNode->data = v;
  
  if (empty()) {
    tail = newNode.get();
    head = move(newNode);
  } else {
    newNode->next = move(head);
    head = move(newNode);
  }
  n++;
}

template <class T> void LinkedList<T>::pop_back() {
  if (empty()) {
    throw out_of_range("pop_back() called on empty list");
  }
  if (n == 1) {
    head = nullptr;
    tail = nullptr;
  } else {
    Node *p = head.get();
    while (p->next.get() != tail) {
      p = p->next.get();
    }
    p->next = nullptr;
    tail = p;
  }
  n--;
}

template <class T> void LinkedList<T>::pop_front() {
  if (empty()) {
    throw out_of_range("pop_front() called on empty list");
  }
  if (n == 1) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = move(head->next);
  }
  n--;
}

template <class T> T &LinkedList<T>::front() {
  if (empty()) {
    throw out_of_range("front() called on empty list");
  }
  return head->data;
}

template <class T> const T &LinkedList<T>::front() const {
  if (empty()) {
    throw out_of_range("front() called on empty list");
  }
  return head->data;
}

template <class T> T &LinkedList<T>::back() {
  if (empty()) {
    throw out_of_range("back() called on empty list");
  }
  return tail->data;
}

template <class T> const T &LinkedList<T>::back() const {
  if (empty()) {
    throw out_of_range("back() called on empty list");
  }
  return tail->data;
}

template <class T> bool LinkedList<T>::empty() const { return n == 0; }

template <class T> void LinkedList<T>::clear() {
  head = nullptr;
  tail = nullptr;
  n = 0;
}

template <class T> int LinkedList<T>::size() const { return n; }

template <class T> void LinkedList<T>::remove(const T &v) {
  if (empty()) {
    throw out_of_range("remove() called on empty list");
  }
  if (head->data == v) {
    pop_front();
    return;
  }
  
  Node *p = head.get();
  while (p->next != nullptr && p->next->data != v) {
    p = p->next.get();
  }
  
  if (p->next == nullptr) {
    throw out_of_range("remove() called on non-existent value");
  }
  
  if (p->next.get() == tail) {
    tail = p;
    p->next = nullptr;
    n--;
  } else {
    p->next = move(p->next->next);
    n--;
  }
}

template <class T> bool LinkedList<T>::contains(const T &v) const {
  const Node *p = head.get();
  while (p != nullptr) {
    if (p->data == v) {
      return true;
    }
    p = p->next.get();
  }
  return false;
}

template class LinkedList<int>;
template class LinkedList<double>;
template class LinkedList<string>;
