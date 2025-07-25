#include "item_manager.h"

#include <fstream>
#include <iostream>

#include "json.hpp"

ItemType ItemManager::StringToItemType(const std::string& type_str) const {
  if (type_str == "kWeapon") return ItemType::kWeapon;
  if (type_str == "kArmor") return ItemType::kArmor;
  if (type_str == "kHealthHealer") return ItemType::kHealthHealer;
  if (type_str == "kSanityHealer") return ItemType::kSanityHealer;
  if (type_str == "kInstantWeapon") return ItemType::kInstantWeapon;

  // �������� �� ���������
  return ItemType::kWeapon;
}

ItemManager::ItemManager() {
  std::ifstream file("items.json");

  auto data = nlohmann::json::parse(file, nullptr, false);

  for (const auto& item_data : data) {
    int id = item_data["id"].get<int>();
    ItemType item_type = StringToItemType(item_data["type"].get<std::string>());

    items_[id] =
        std::make_unique<Item>(id, item_data["name"].get<std::string>(),
                               item_data["description"].get<std::string>(),
                               item_type, item_data["value"].get<int>());
  }
}

Item* ItemManager::GetItem(int id) const {
  auto it = items_.find(id);
  if (it == items_.end()) {
    return nullptr;
  }
  return it->second.get();
}
