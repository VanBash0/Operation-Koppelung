#ifndef ITEM_MANAGER_H_
#define ITEM_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "item.h"

class ItemManager {
 public:
  ItemManager();

  // Возвращает shared_ptr на Item, или nullptr, если такого нет
  Item* GetItem(int id) const;

 private:
  std::unordered_map<int, std::unique_ptr<Item>> items_;

  // Вспомогательная функция для конвертации строки в ItemType
  ItemType StringToItemType(const std::string& type_str) const;
};

#endif  // ITEM_MANAGER_H_
