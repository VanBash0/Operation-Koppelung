#include "enemy_manager.h"

#include <fstream>
#include <memory>

#include "json.hpp"

EnemyManager::EnemyManager(AttackManager* attack_manager) {
  std::ifstream file("enemies.json");
  nlohmann::json data = nlohmann::json::parse(file);

  for (const auto& enemy_data : data) {
    int id = enemy_data["id"];
    std::vector<Attack*> attacks;
    for (int i : enemy_data["attack_ids"]) {
      attacks.push_back(attack_manager->GetAttack(i));
    }
    enemies_[id] =
        std::make_unique<Enemy>(enemy_data["name"].get<std::string>(),
                                enemy_data["description"].get<std::string>(),
                                enemy_data["health"].get<int>(), attacks);
  }
}

std::unique_ptr<Enemy> EnemyManager::GetEnemy(int id) const {
  return std::make_unique<Enemy>(*enemies_.at(id));
}
