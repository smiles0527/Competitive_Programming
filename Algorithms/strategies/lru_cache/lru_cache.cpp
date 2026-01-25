#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <list>
#include <unordered_map>

/**
 * LRU (Least Recently Used) Cache implementation.
 * 
 * The cache has a fixed capacity. When the cache is full and a new key-value pair
 * is added, the least recently used pair is evicted to make room for the new one.
 */
class LRUCache {
public:
    /**
     * Initialize the LRU cache with a positive capacity.
     * @param capacity Maximum number of key-value pairs the cache can hold
     */
    explicit LRUCache(int capacity);
    
    /**
     * Return the value of the key if it exists, otherwise return -1.
     * Accessing a key makes it the most recently used.
     * @param key Key to look up
     * @return Value associated with the key, or -1 if not found
     */
    int get(int key);
    
    /**
     * Update the value of the key if it exists. Otherwise, add the key-value pair.
     * If the cache is at capacity, evict the least recently used key.
     * @param key Key to insert or update
     * @param value Value to associate with the key
     */
    void put(int key, int value);

private:
    int capacity_;
    std::list<std::pair<int, int>> cache_; // front = most recent, back = least recent
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map_;
    
    void moveToFront(std::list<std::pair<int, int>>::iterator it);
};


// Implementation

LRUCache::LRUCache(int capacity) : capacity_(capacity) {}

void LRUCache::moveToFront(std::list<std::pair<int, int>>::iterator it) {
    if (it != cache_.begin()) {
        cache_.splice(cache_.begin(), cache_, it);
    }
}

int LRUCache::get(int key) {
    auto it = map_.find(key);
    if (it == map_.end()) {
        return -1;
    }
    
    // Move to front (most recently used)
    moveToFront(it->second);
    return it->second->second;
}

void LRUCache::put(int key, int value) {
    auto it = map_.find(key);
    
    if (it != map_.end()) {
        // Key exists, update value and move to front
        it->second->second = value;
        moveToFront(it->second);
    } else {
        // Key doesn't exist
        if (static_cast<int>(cache_.size()) >= capacity_) {
            // Evict least recently used (back of list)
            int evictKey = cache_.back().first;
            cache_.pop_back();
            map_.erase(evictKey);
        }
        
        // Add new entry to front
        cache_.push_front({key, value});
        map_[key] = cache_.begin();
    }
}

