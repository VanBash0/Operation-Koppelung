#include "enemy_manager.h"

#include <fstream>
#include <memory>

#include "json.hpp"

EnemyManager::EnemyManager(std::shared_ptr<AttackManager> attackManager) {
  std::ifstream file("enemies.json");
  nlohmann::json data = nlohmann::json::parse(file);

  for (const auto& enemyData : data) {
    int id = enemyData["id"];
    std::vector<std::shared_ptr<Attack>> attacks;
    for (int i : enemyData["attack_ids"]) {
      attacks.push_back(attackManager->GetAttack(i));
    }
    enemies_[id] =
        std::make_unique<Enemy>(enemyData["name"].get<std::string>(),
                                enemyData["description"].get<std::string>(),
                                enemyData["health"].get<int>(), attacks);
  }
}

std::unique_ptr<Enemy> EnemyManager::GetEnemy(int id) const {
  return std::make_unique<Enemy>(*enemies_.at(id));
}
