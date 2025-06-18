#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "attack_manager.h"
#include "enemy.h"

class EnemyManager {
 public:
  EnemyManager(AttackManager* attack_manager);

  // Возвращает копию врага по id
  std::unique_ptr<Enemy> GetEnemy(int id) const;

 private:
  std::unordered_map<int, std::unique_ptr<Enemy>> enemies_;
};

#endif  // ENEMY_MANAGER_H_
