#include <bits/stdc++.h>

using namespace std;

template <class T> class AvlTree {

public:
  AvlTree();
  AvlTree(const AvlTree<T> &t);
  AvlTree<T> &operator=(const AvlTree<T> &t);
  ~AvlTree();

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
  void balance(unique_ptr<Node> &p);
  void rotate_left(unique_ptr<Node> &p);
  void rotate_right(unique_ptr<Node> &p);
};

template <class T> AvlTree<T>::AvlTree() : root(nullptr), n(0) {}

template <class T>
AvlTree<T>::AvlTree(const AvlTree<T> &t) : root(nullptr), n(0) {
  for (const auto &v : t.in_order_traversal()) {
    insert(v);
  }
}

template <class T> AvlTree<T> &AvlTree<T>::operator=(const AvlTree<T> &t) {
  if (this != &t) {
    clear();
    for (const auto &v : t.in_order_traversal()) {
      insert(v);
    }
  }
  return *this;
}

template <class T> AvlTree<T>::~AvlTree() { clear(); }

template <class T> void AvlTree<T>::insert(const T &v) { insert(v, root); }

template <class T> void AvlTree<T>::remove(const T &v) { remove(v, root); }

template <class T> bool AvlTree<T>::contains(const T &v) const {
  return contains(v, root);
}

template <class T> T AvlTree<T>::find_min() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->left != nullptr) {
    p = p->left.get();
  }
  return p->data;
}

template <class T> T AvlTree<T>::find_max() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->right != nullptr) {
    p = p->right.get();
  }
  return p->data;
}

template <class T> void AvlTree<T>::clear() { clear(root); }

template <class T> int AvlTree<T>::height() const { return height(root); }

template <class T> int AvlTree<T>::size() const { return n; }

template <class T> bool AvlTree<T>::empty() const { return n == 0; }

template <class T> vector<T> AvlTree<T>::in_order_traversal() const {
  vector<T> v;
  in_order_traversal(root, v);
  return v;
}

template <class T> vector<T> AvlTree<T>::pre_order_traversal() const {
  vector<T> v;
  pre_order_traversal(root, v);
  return v;
}

template <class T> vector<T> AvlTree<T>::post_order_traversal() const {
  vector<T> v;
  post_order_traversal(root, v);
  return v;
}

template <class T>
void AvlTree<T>::insert(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    p = make_unique<Node>();
    p->data = v;
    n++;
  } else if (v < p->data) {
    insert(v, p->left);
  } else if (v > p->data) {
    insert(v, p->right);
  } else {
    throw invalid_argument("duplicate value");
  }
  balance(p);
}

template <class T>
void AvlTree<T>::remove(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    throw invalid_argument("value not found");
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
      // Find in-order predecessor
      Node *pred = p->left.get();
      while (pred->right != nullptr) {
        pred = pred->right.get();
      }
      p->data = pred->data;
      remove(pred->data, p->left);
    }
  }
  if (p != nullptr) {
    balance(p);
  }
}

template <class T>
bool AvlTree<T>::contains(const T &v, const unique_ptr<Node> &p) const {
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

template <class T> void AvlTree<T>::clear(unique_ptr<Node> &p) {
  if (p != nullptr) {
    clear(p->left);
    clear(p->right);
    p = nullptr;
    n--;
  }
}

template <class T> int AvlTree<T>::height(const unique_ptr<Node> &p) const {
  if (p == nullptr) {
    return 0;
  } else {
    return 1 + max(height(p->left), height(p->right));
  }
}

template <class T>
void AvlTree<T>::in_order_traversal(const unique_ptr<Node> &p,
                                    vector<T> &v) const {
  if (p != nullptr) {
    in_order_traversal(p->left, v);
    v.push_back(p->data);
    in_order_traversal(p->right, v);
  }
}

template <class T>
void AvlTree<T>::pre_order_traversal(const unique_ptr<Node> &p,
                                     vector<T> &v) const {
  if (p != nullptr) {
    v.push_back(p->data);
    pre_order_traversal(p->left, v);
    pre_order_traversal(p->right, v);
  }
}

template <class T>
void AvlTree<T>::post_order_traversal(const unique_ptr<Node> &p,
                                      vector<T> &v) const {
  if (p != nullptr) {
    post_order_traversal(p->left, v);
    post_order_traversal(p->right, v);
    v.push_back(p->data);
  }
}

template <class T> void AvlTree<T>::balance(unique_ptr<Node> &p) {
  if (p == nullptr) {
    return;
  }
  
  int leftHeight = height(p->left);
  int rightHeight = height(p->right);
  
  if (leftHeight - rightHeight > 1) {
    // Left-heavy
    if (height(p->left->left) >= height(p->left->right)) {
      // Left-Left case
      rotate_right(p);
    } else {
      // Left-Right case
      rotate_left(p->left);
      rotate_right(p);
    }
  } else if (rightHeight - leftHeight > 1) {
    // Right-heavy
    if (height(p->right->right) >= height(p->right->left)) {
      // Right-Right case
      rotate_left(p);
    } else {
      // Right-Left case
      rotate_right(p->right);
      rotate_left(p);
    }
  }
}

template <class T> void AvlTree<T>::rotate_left(unique_ptr<Node> &p) {
  unique_ptr<Node> r = move(p->right);
  p->right = move(r->left);
  r->left = move(p);
  p = move(r);
}

template <class T> void AvlTree<T>::rotate_right(unique_ptr<Node> &p) {
  unique_ptr<Node> l = move(p->left);
  p->left = move(l->right);
  l->right = move(p);
  p = move(l);
}

template class AvlTree<int>;
template class AvlTree<string>;
template class AvlTree<double>;
template class AvlTree<float>;
