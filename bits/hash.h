#ifndef BITS_HASH_H
#define BITS_HASH_H

#include <functional>
#include <utility>

// Custom hash function for pair<T1, T2>
namespace std {
template <class T1, class T2>
struct hash<pair<T1, T2>> {
  size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1);
  }
};
}

#endif
