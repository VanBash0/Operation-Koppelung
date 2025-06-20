#ifndef ITEM_MANAGER_H_
#define ITEM_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "item.h"

class ItemManager {
 public:
  ItemManager();

  // ���������� shared_ptr �� Item, ��� nullptr, ���� ������ ���
  Item* GetItem(int id) const;

 private:
  std::unordered_map<int, std::unique_ptr<Item>> items_;

  // ��������������� ������� ��� ����������� ������ � ItemType
  ItemType StringToItemType(const std::string& type_str) const;
};

#endif  // ITEM_MANAGER_H_
