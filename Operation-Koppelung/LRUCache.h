#pragma once
#include <unordered_map>
#include <memory>
#include <list>

template <typename Value>
class LRUCache {
public:
	LRUCache(size_t capacity);
	void put(int key, std::shared_ptr<Value> value);
	std::shared_ptr<Value> get(int key);
	bool contains(int key) const;
private:
	struct CacheItem {
		std::shared_ptr<Value> value;
		std::list<int>::iterator it;
	};

	void touch(typename std::unordered_map<int, CacheItem>::iterator it);

	std::unordered_map<int, CacheItem> cache;
	std::list<int> order;
	int capacity;
};