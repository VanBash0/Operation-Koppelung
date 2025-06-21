#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <list>
#include <memory>
#include <unordered_map>

// Класс кэша с вытеснением по принципу Least Recently Used (LRU)
// Хранит пары ключ-значение и удаляет наименее недавно использованные элементы
// при переполнении
template <typename Value>
class LRUCache {
 public:
  explicit LRUCache(size_t capacity) : capacity_(capacity) {}

  void Put(int key, std::unique_ptr<Value> value) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      Touch(it);
    } else {
      if (cache_.size() == capacity_) {
        // Удаляем наименее недавно использованный элемент
        cache_.erase(order_.back());
        order_.pop_back();
      }
      // Вставляем новый элемент в начало списка
      order_.push_front(key);
      cache_[key] = {std::move(value), order_.begin()};
    }
  }

  Value* Get(int key) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      Touch(it);
      return it->second.value.get();
    }
    return nullptr;
  }

  bool Contains(int key) const { return cache_.find(key) != cache_.end(); }

 private:
  struct CacheItem {
    std::unique_ptr<Value> value;
    std::list<int>::iterator it;  // Указатель на позицию ключа в списке order_
  };

  // Перемещает элемент в начало списка (делает его недавно использованным)
  void Touch(typename std::unordered_map<int, CacheItem>::iterator it) {
    order_.erase(it->second.it);
    order_.push_front(it->first);
    it->second.it = order_.begin();
  }

  // Обновляет порядок использования для указанного ключа
  void UpdateOrder(int key) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      order_.erase(it->second.it);
      order_.push_front(key);
      it->second.it = order_.begin();
    }
  }

  std::unordered_map<int, CacheItem> cache_;
  std::list<int> order_;  // Список ключей
  size_t capacity_;       // Максимальное количество элементов в кэше
};

#endif  // LRU_CACHE_H_
