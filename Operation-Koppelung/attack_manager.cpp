#include "attack_manager.h"

#include <fstream>

#include "json.hpp"

AttackManager::AttackManager() {
  std::ifstream file("attacks.json");
  nlohmann::json data = nlohmann::json::parse(file);

  for (const auto& attackData : data) {
    int id = attackData["id"];
    std::string name = attackData["name"];
    std::string description = attackData["description"];
    int damage = attackData["damage"];
    int sanity_cost = attackData["sanity_cost"];

    attacks_[id] =
        std::make_shared<Attack>(name, description, damage, sanity_cost);
  }
}

std::shared_ptr<Attack> AttackManager::GetAttack(int id) const {
  auto it = attacks_.find(id);
  if (it != attacks_.end()) {
    return it->second;
  }
  return nullptr;
}
