#include <bits/stdc++.h>

using namespace std;

template <class T> class BinarySearchTree {

public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree<T> &t);
  BinarySearchTree<T> &operator=(const BinarySearchTree<T> &t);
  ~BinarySearchTree();

  void insert(const T &v);
  void remove(const T &v);
  bool contains(const T &v) const;
  T find_min() const;
  T find_max() const;
  void clear();
  int height() const;
  int size() const;
  bool empty() const;
  vector<T> in_order_traversal() const;
  vector<T> pre_order_traversal() const;
  vector<T> post_order_traversal() const;

private:
  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
  };

  unique_ptr<Node> root;
  int n;

  void insert(const T &v, unique_ptr<Node> &p);
  void remove(const T &v, unique_ptr<Node> &p);
  bool contains(const T &v, const unique_ptr<Node> &p) const;
  void clear(unique_ptr<Node> &p);
  int height(const unique_ptr<Node> &p) const;
  void in_order_traversal(const unique_ptr<Node> &p,
                          vector<T> &v) const;
  void pre_order_traversal(const unique_ptr<Node> &p,
                           vector<T> &v) const;
  void post_order_traversal(const unique_ptr<Node> &p,
                            vector<T> &v) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), n(0) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &t)
    : root(nullptr), n(0) {
  for (const auto &v : t.in_order_traversal()) {
    insert(v);
  }
}

template <class T>
BinarySearchTree<T> &
BinarySearchTree<T>::operator=(const BinarySearchTree<T> &t) {
  if (this != &t) {
    clear();
    for (const auto &v : t.in_order_traversal()) {
      insert(v);
    }
  }
  return *this;
}

template <class T> BinarySearchTree<T>::~BinarySearchTree() { clear(); }

template <class T> void BinarySearchTree<T>::insert(const T &v) {
  insert(v, root);
}

template <class T> void BinarySearchTree<T>::remove(const T &v) {
  remove(v, root);
}

template <class T> bool BinarySearchTree<T>::contains(const T &v) const {
  return contains(v, root);
}

template <class T> T BinarySearchTree<T>::find_min() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->left != nullptr) {
    p = p->left.get();
  }
  return p->data;
}

template <class T> T BinarySearchTree<T>::find_max() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->right != nullptr) {
    p = p->right.get();
  }
  return p->data;
}

template <class T> void BinarySearchTree<T>::clear() {
  clear(root);
  n = 0;
}

template <class T> int BinarySearchTree<T>::height() const {
  return height(root);
}

template <class T> int BinarySearchTree<T>::size() const { return n; }

template <class T> bool BinarySearchTree<T>::empty() const { return n == 0; }

template <class T>
vector<T> BinarySearchTree<T>::in_order_traversal() const {
  vector<T> v;
  in_order_traversal(root, v);
  return v;
}

template <class T>
vector<T> BinarySearchTree<T>::pre_order_traversal() const {
  vector<T> v;
  pre_order_traversal(root, v);
  return v;
}

template <class T>
vector<T> BinarySearchTree<T>::post_order_traversal() const {
  vector<T> v;
  post_order_traversal(root, v);
  return v;
}

template <class T>
void BinarySearchTree<T>::insert(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    p = make_unique<Node>();
    p->data = v;
    n++;
  } else if (v < p->data) {
    insert(v, p->left);
  } else if (v > p->data) {
    insert(v, p->right);
  } else {
    throw invalid_argument("Value already exists in tree");
  }
}

template <class T>
void BinarySearchTree<T>::remove(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    throw invalid_argument("Value does not exist in tree");
  } else if (v < p->data) {
    remove(v, p->left);
  } else if (v > p->data) {
    remove(v, p->right);
  } else {
    if (p->left == nullptr && p->right == nullptr) {
      p = nullptr;
      n--;
    } else if (p->left == nullptr) {
      p = move(p->right);
      n--;
    } else if (p->right == nullptr) {
      p = move(p->left);
      n--;
    } else {
      // Find in-order successor
      Node *successor = p->right.get();
      while (successor->left != nullptr) {
        successor = successor->left.get();
      }
      p->data = successor->data;
      remove(successor->data, p->right);
    }
  }
}

template <class T>
bool BinarySearchTree<T>::contains(const T &v,
                                   const unique_ptr<Node> &p) const {
  if (p == nullptr) {
    return false;
  } else if (v < p->data) {
    return contains(v, p->left);
  } else if (v > p->data) {
    return contains(v, p->right);
  } else {
    return true;
  }
}

template <class T> void BinarySearchTree<T>::clear(unique_ptr<Node> &p) {
  if (p != nullptr) {
    clear(p->left);
    clear(p->right);
    p = nullptr;
  }
}

template <class T>
int BinarySearchTree<T>::height(const unique_ptr<Node> &p) const {
  if (p == nullptr) {
    return 0;
  } else {
    return 1 + max(height(p->left), height(p->right));
  }
}

template <class T>
void BinarySearchTree<T>::in_order_traversal(const unique_ptr<Node> &p,
                                             vector<T> &v) const {
  if (p != nullptr) {
    in_order_traversal(p->left, v);
    v.push_back(p->data);
    in_order_traversal(p->right, v);
  }
}

template <class T>
void BinarySearchTree<T>::pre_order_traversal(const unique_ptr<Node> &p,
                                              vector<T> &v) const {
  if (p != nullptr) {
    v.push_back(p->data);
    pre_order_traversal(p->left, v);
    pre_order_traversal(p->right, v);
  }
}

template <class T>
void BinarySearchTree<T>::post_order_traversal(const unique_ptr<Node> &p,
                                               vector<T> &v) const {
  if (p != nullptr) {
    post_order_traversal(p->left, v);
    post_order_traversal(p->right, v);
    v.push_back(p->data);
  }
}

template class BinarySearchTree<char>;
template class BinarySearchTree<int>;
template class BinarySearchTree<string>;
template class BinarySearchTree<double>;
template class BinarySearchTree<float>;
