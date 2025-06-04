#include "item_manager.h"

#include <fstream>
#include <iostream>

#include "json.hpp"

using json = nlohmann::json;

ItemType ItemManager::StringToItemType(const std::string& type_str) const {
  if (type_str == "kWeapon") return ItemType::kWeapon;
  if (type_str == "kArmor") return ItemType::kArmor;
  if (type_str == "kHpHealer") return ItemType::kHpHealer;
  if (type_str == "kSanityHealer") return ItemType::kSanityHealer;
  if (type_str == "kInstantWeapon") return ItemType::kInstantWeapon;

  // Значение по умолчанию
  return ItemType::kWeapon;
}

ItemManager::ItemManager() {
  std::ifstream file("items.json");
  if (!file.is_open()) {
    std::cerr << "Failed to open items.json\n";
    return;
  }

  auto data = json::parse(file, nullptr, false);
  if (data.is_discarded()) {
    std::cerr << "Failed to parse items.json\n";
    return;
  }

  for (const auto& itemData : data) {
    int id = itemData["id"].get<int>();
    ItemType item_type = StringToItemType(itemData["type"].get<std::string>());

    items_[id] =
        std::make_unique<Item>(id, itemData["name"].get<std::string>(),
                               itemData["description"].get<std::string>(),
                               item_type, itemData["value"].get<int>());
  }
}

std::shared_ptr<Item> ItemManager::GetItem(int id) const {
  auto it = items_.find(id);
  if (it == items_.end()) {
    return nullptr;
  }
  return std::make_shared<Item>(*it->second);
}
