#include <bits/stdc++.h>

using namespace std;

template <class Key, class Value> class HashTable {

public:
  HashTable(function<int(Key)> hash_function, int size = 10);
  ~HashTable();
  void add(Key key, Value value);
  Value get(Key key) const;
  void remove(Key key);
  bool contains(Key key) const;
  unsigned int size() const;
  bool empty() const;
  void clear();
  Value &operator[](Key key);
  const Value &operator[](Key key) const;

private:
  function<int(Key)> hash_function;
  int _num_elements;
  int _size;
  float load_factor;
  vector<shared_ptr<vector<pair<Key, Value>>>> table;
  void grow();
  void shrink();
  int hash_index(Key key) const;
};

template <class Key, class Value>
HashTable<Key, Value>::HashTable(function<int(Key)> hash_function,
                                 int size)
    : hash_function(hash_function), _num_elements(0), _size(size),
      load_factor(0.75f),
      table(size) {}

template <class Key, class Value> HashTable<Key, Value>::~HashTable() {
  table.clear();
}

template <class Key, class Value>
int HashTable<Key, Value>::hash_index(Key key) const {
  // Handle negative hash values
  int hash = hash_function(key);
  return abs(hash) % _size;
}

template <class Key, class Value>
void HashTable<Key, Value>::add(Key key, Value value) {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    table[index] = make_shared<vector<pair<Key, Value>>>();
  }
  
  // Check if key already exists and update it
  for (auto &pair : *table[index]) {
    if (pair.first == key) {
      pair.second = value;
      return;
    }
  }
  
  table[index]->push_back(make_pair(key, value));
  _num_elements++;
  
  if (static_cast<float>(_num_elements) / _size > load_factor) {
    grow();
  }
}

template <class Key, class Value>
Value HashTable<Key, Value>::get(Key key) const {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    throw invalid_argument("Key not found");
  }
  for (const auto &pair : *table[index]) {
    if (pair.first == key) {
      return pair.second;
    }
  }
  throw invalid_argument("Key not found");
}

template <class Key, class Value> void HashTable<Key, Value>::remove(Key key) {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    throw invalid_argument("Key not found");
  }
  for (auto it = table[index]->begin(); it != table[index]->end(); ++it) {
    if (it->first == key) {
      table[index]->erase(it);
      _num_elements--;
      if (_size > 10 &&
          static_cast<float>(_num_elements) / _size < load_factor / 2) {
        shrink();
      }
      return;
    }
  }
  throw invalid_argument("Key not found");
}

template <class Key, class Value>
bool HashTable<Key, Value>::contains(Key key) const {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    return false;
  }
  for (const auto &pair : *table[index]) {
    if (pair.first == key) {
      return true;
    }
  }
  return false;
}

template <class Key, class Value>
unsigned int HashTable<Key, Value>::size() const {
  return _num_elements;
}

template <class Key, class Value> bool HashTable<Key, Value>::empty() const {
  return _num_elements == 0;
}

template <class Key, class Value> void HashTable<Key, Value>::clear() {
  for (auto &bucket : table) {
    bucket = nullptr;
  }
  _num_elements = 0;
}

template <class Key, class Value>
Value &HashTable<Key, Value>::operator[](Key key) {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    throw invalid_argument("Key not found");
  }
  for (auto &pair : *table[index]) {
    if (pair.first == key) {
      return pair.second;
    }
  }
  throw invalid_argument("Key not found");
}

template <class Key, class Value>
const Value &HashTable<Key, Value>::operator[](Key key) const {
  int index = hash_index(key);
  if (table[index] == nullptr) {
    throw invalid_argument("Key not found");
  }
  for (const auto &pair : *table[index]) {
    if (pair.first == key) {
      return pair.second;
    }
  }
  throw invalid_argument("Key not found");
}

template <class Key, class Value> void HashTable<Key, Value>::grow() {
  int new_size = _size * 2;
  vector<shared_ptr<vector<pair<Key, Value>>>> new_table(new_size);
  
  int old_size = _size;
  _size = new_size;
  
  for (int i = 0; i < old_size; i++) {
    if (table[i] != nullptr) {
      for (const auto &pair : *table[i]) {
        int index = hash_index(pair.first);
        if (new_table[index] == nullptr) {
          new_table[index] =
              make_shared<vector<pair<Key, Value>>>();
        }
        new_table[index]->push_back(pair);
      }
    }
  }
  table = move(new_table);
}

template <class Key, class Value> void HashTable<Key, Value>::shrink() {
  int new_size = _size / 2;
  if (new_size < 10) {
    new_size = 10;
  }
  
  vector<shared_ptr<vector<pair<Key, Value>>>> new_table(new_size);
  
  int old_size = _size;
  _size = new_size;
  
  for (int i = 0; i < old_size; i++) {
    if (table[i] != nullptr) {
      for (const auto &pair : *table[i]) {
        int index = hash_index(pair.first);
        if (new_table[index] == nullptr) {
          new_table[index] =
              make_shared<vector<pair<Key, Value>>>();
        }
        new_table[index]->push_back(pair);
      }
    }
  }
  table = move(new_table);
}

template class HashTable<string, int>;
template class HashTable<int, int>;
template class HashTable<string, string>;
