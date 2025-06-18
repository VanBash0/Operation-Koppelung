#include "attack_manager.h"

#include <fstream>

#include "json.hpp"

AttackManager::AttackManager() {
  std::ifstream file("attacks.json");
  nlohmann::json data = nlohmann::json::parse(file);

  for (const auto& attack_data : data) {
    int id = attack_data["id"];
    std::string name = attack_data["name"];
    std::string description = attack_data["description"];
    int damage = attack_data["damage"];
    int sanity_cost = attack_data["sanity_cost"];
    bool is_damaging = attack_data["is_damaging"];
    bool is_physical = attack_data["is_physical"];

    attacks_[id] = std::make_unique<Attack>(
        id, damage, sanity_cost, name, description, is_damaging, is_physical);
  }
}

Attack* AttackManager::GetAttack(int id) const {
  auto it = attacks_.find(id);
  if (it != attacks_.end()) {
    return it->second.get();
  }
  return nullptr;
}
