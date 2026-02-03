#include <bits/stdc++.h>

using namespace std;

template <class T> class RedBlackTree {

public:
  RedBlackTree();
  RedBlackTree(const RedBlackTree<T> &t);
  RedBlackTree<T> &operator=(const RedBlackTree<T> &t);
  ~RedBlackTree();

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
    bool is_red;
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

template <class T> RedBlackTree<T>::RedBlackTree() : root(nullptr), n(0) {}

template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &t) : root(nullptr), n(0) {
  for (const auto &v : t.in_order_traversal()) {
    insert(v);
  }
}

template <class T>
RedBlackTree<T> &RedBlackTree<T>::operator=(const RedBlackTree<T> &t) {
  if (this != &t) {
    clear();
    for (const auto &v : t.in_order_traversal()) {
      insert(v);
    }
  }
  return *this;
}

template <class T> RedBlackTree<T>::~RedBlackTree() { clear(); }

template <class T> void RedBlackTree<T>::insert(const T &v) {
  insert(v, root);
  if (root != nullptr) {
    root->is_red = false;
  }
}

template <class T> void RedBlackTree<T>::remove(const T &v) {
  remove(v, root);
  if (root != nullptr) {
    root->is_red = false;
  }
}

template <class T> bool RedBlackTree<T>::contains(const T &v) const {
  return contains(v, root);
}

template <class T> T RedBlackTree<T>::find_min() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->left != nullptr) {
    p = p->left.get();
  }
  return p->data;
}

template <class T> T RedBlackTree<T>::find_max() const {
  if (root == nullptr) {
    throw out_of_range("Tree is empty");
  }
  const Node *p = root.get();
  while (p->right != nullptr) {
    p = p->right.get();
  }
  return p->data;
}

template <class T> void RedBlackTree<T>::clear() {
  clear(root);
  n = 0;
}

template <class T> int RedBlackTree<T>::height() const { return height(root); }

template <class T> int RedBlackTree<T>::size() const { return n; }

template <class T> bool RedBlackTree<T>::empty() const { return n == 0; }

template <class T> vector<T> RedBlackTree<T>::in_order_traversal() const {
  vector<T> v;
  in_order_traversal(root, v);
  return v;
}

template <class T> vector<T> RedBlackTree<T>::pre_order_traversal() const {
  vector<T> v;
  pre_order_traversal(root, v);
  return v;
}

template <class T>
vector<T> RedBlackTree<T>::post_order_traversal() const {
  vector<T> v;
  post_order_traversal(root, v);
  return v;
}

template <class T>
void RedBlackTree<T>::insert(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    p = make_unique<Node>();
    p->data = v;
    p->is_red = true;
    n++;
  } else if (v < p->data) {
    insert(v, p->left);
  } else if (v > p->data) {
    insert(v, p->right);
  } else {
    throw invalid_argument("Value already exists in tree");
  }
  balance(p);
}

template <class T>
void RedBlackTree<T>::remove(const T &v, unique_ptr<Node> &p) {
  if (p == nullptr) {
    return;
  }
  
  if (v < p->data) {
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
  
  if (p != nullptr) {
    balance(p);
  }
}

template <class T>
bool RedBlackTree<T>::contains(const T &v,
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

template <class T> void RedBlackTree<T>::clear(unique_ptr<Node> &p) {
  if (p != nullptr) {
    clear(p->left);
    clear(p->right);
    p = nullptr;
  }
}

template <class T>
int RedBlackTree<T>::height(const unique_ptr<Node> &p) const {
  if (p == nullptr) {
    return 0;
  } else {
    return 1 + max(height(p->left), height(p->right));
  }
}

template <class T>
void RedBlackTree<T>::in_order_traversal(const unique_ptr<Node> &p,
                                         vector<T> &v) const {
  if (p != nullptr) {
    in_order_traversal(p->left, v);
    v.push_back(p->data);
    in_order_traversal(p->right, v);
  }
}

template <class T>
void RedBlackTree<T>::pre_order_traversal(const unique_ptr<Node> &p,
                                          vector<T> &v) const {
  if (p != nullptr) {
    v.push_back(p->data);
    pre_order_traversal(p->left, v);
    pre_order_traversal(p->right, v);
  }
}

template <class T>
void RedBlackTree<T>::post_order_traversal(const unique_ptr<Node> &p,
                                           vector<T> &v) const {
  if (p != nullptr) {
    post_order_traversal(p->left, v);
    post_order_traversal(p->right, v);
    v.push_back(p->data);
  }
}

template <class T> void RedBlackTree<T>::balance(unique_ptr<Node> &p) {
  if (p == nullptr) {
    return;
  }

  // Color flip
  if (p->left != nullptr && p->left->is_red && p->right != nullptr &&
      p->right->is_red) {
    p->is_red = true;
    p->left->is_red = false;
    p->right->is_red = false;
    return;
  }

  // Left subtree cases
  if (p->left != nullptr && p->left->is_red) {
    if (p->left->left != nullptr && p->left->left->is_red) {
      // Left-Left case
      rotate_right(p);
      p->is_red = false;
      if (p->right != nullptr) {
        p->right->is_red = true;
      }
    } else if (p->left->right != nullptr && p->left->right->is_red) {
      // Left-Right case
      rotate_left(p->left);
      rotate_right(p);
      p->is_red = false;
      if (p->right != nullptr) {
        p->right->is_red = true;
      }
    }
  }

  // Right subtree cases
  if (p->right != nullptr && p->right->is_red) {
    if (p->right->right != nullptr && p->right->right->is_red) {
      // Right-Right case
      rotate_left(p);
      p->is_red = false;
      if (p->left != nullptr) {
        p->left->is_red = true;
      }
    } else if (p->right->left != nullptr && p->right->left->is_red) {
      // Right-Left case
      rotate_right(p->right);
      rotate_left(p);
      p->is_red = false;
      if (p->left != nullptr) {
        p->left->is_red = true;
      }
    }
  }
}

template <class T> void RedBlackTree<T>::rotate_left(unique_ptr<Node> &p) {
  unique_ptr<Node> r = move(p->right);
  p->right = move(r->left);
  r->left = move(p);
  p = move(r);
}

template <class T>
void RedBlackTree<T>::rotate_right(unique_ptr<Node> &p) {
  unique_ptr<Node> l = move(p->left);
  p->left = move(l->right);
  l->right = move(p);
  p = move(l);
}

template class RedBlackTree<int>;
template class RedBlackTree<string>;
template class RedBlackTree<double>;
template class RedBlackTree<float>;
