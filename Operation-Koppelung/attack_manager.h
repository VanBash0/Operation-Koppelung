#ifndef ATTACK_MANAGER_H_
#define ATTACK_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "attack.h"

// Менеджер атак: хранит атаки по их ID
class AttackManager {
 public:
  explicit AttackManager();

  // Возвращает указатель на атаку по ID или nullptr, если не найдено
  Attack* GetAttack(int id) const;

 private:
  std::unordered_map<int, std::unique_ptr<Attack>> attacks_;
};

#endif  // ATTACK_MANAGER_H_
