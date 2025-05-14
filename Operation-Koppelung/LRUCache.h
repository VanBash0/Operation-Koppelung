#pragma once
#include <unordered_map>
#include <memory>
#include <list>

template <typename Value>
class LRUCache {
public:
	LRUCache(size_t capacity) : capacity(capacity) {};

	void put(int key, std::shared_ptr<Value> value) {
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
			cache[key] = { value, order.begin() };
		}
	};

	std::shared_ptr<Value> get(int key) {
		auto it = cache.find(key);
		if (it != cache.end()) {
			touch(it);
			return it->second.value;
		}
		return nullptr;
	};

	bool contains(int key) const {
		return cache.find(key) != cache.end();
	};
private:
	struct CacheItem {
		std::shared_ptr<Value> value;
		std::list<int>::iterator it;
	};

	void touch(typename std::unordered_map<int, CacheItem>::iterator it) {
		order.erase(it->second.it);
		order.push_front(it->first);
		it->second.it = order.begin();
	}

	std::unordered_map<int, CacheItem> cache;
	std::list<int> order;
	int capacity;
};