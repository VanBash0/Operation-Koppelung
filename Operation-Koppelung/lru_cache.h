#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <list>
#include <memory>
#include <unordered_map>

// ����� ���� � ����������� �� �������� Least Recently Used (LRU)
// ������ ���� ����-�������� � ������� �������� ������� �������������� ��������
// ��� ������������
template <typename Value>
class LRUCache {
 public:
  explicit LRUCache(size_t capacity) : capacity_(capacity) {}

  void Put(int key, std::shared_ptr<Value> value) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      Touch(it);
    } else {
      if (cache_.size() == capacity_) {
        // ������� �������� ������� �������������� �������
        cache_.erase(order_.back());
        order_.pop_back();
      }
      // ��������� ����� ������� � ������ ������
      order_.push_front(key);
      cache_[key] = {value, order_.begin()};
    }
  }

  std::shared_ptr<Value> Get(int key) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      Touch(it);
      return it->second.value;
    }
    return nullptr;
  }

  bool Contains(int key) const { return cache_.find(key) != cache_.end(); }

 private:
  struct CacheItem {
    std::shared_ptr<Value> value;
    std::list<int>::iterator it;  // ��������� �� ������� ����� � ������ order_
  };

  // ���������� ������� � ������ ������ (������ ��� ������� ��������������)
  void Touch(typename std::unordered_map<int, CacheItem>::iterator it) {
    order_.erase(it->second.it);
    order_.push_front(it->first);
    it->second.it = order_.begin();
  }

  std::unordered_map<int, CacheItem> cache_;
  std::list<int> order_;  // ������ ������
  size_t capacity_;       // ������������ ���������� ��������� � ����
};

#endif  // LRU_CACHE_H_
