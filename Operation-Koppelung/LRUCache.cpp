#include "LRUCache.h"

template <typename Value>
LRUCache<Value>::LRUCache(size_t capacity) : capacity(capacity) {}

template <typename Value>
void LRUCache<Value>::put(int key, std::shared_ptr<Value> value) {
	auto it = cache.find(key);
	if (it != cache.end()) {
		touch(it);
	}
	else {
		if (cache.size() == capacity) {
			cache.erase(order.back());
			order.pop_back();
		}
		order.push_front(key);
		cache[key] = {value, order.begin()};
	}
}

template <typename Value>
std::shared_ptr<Value> LRUCache<Value>::get(int key) {
	auto it = cache.find(key);
	if (it != cache.end()) {
		touch(it);
		return it->second.first;
	}
	return nullptr;
}

template <typename Value>
bool LRUCache<Value>::contains(int key) const {
	return cache.find(key) != cache.end();
}

template <typename Value>
void LRUCache<Value>::touch(typename std::unordered_map<int, CacheItem>::iterator it) {
	order.erase(it->second.it);
	order.push_front(it->first);
	it->second.it = order.begin();
}