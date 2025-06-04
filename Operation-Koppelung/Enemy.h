#ifndef ENEMY_H_
#define ENEMY_H_

#include <memory>
#include <string>
#include <vector>

#include "attack.h"

class Enemy {
 public:
  Enemy(const std::string& name, const std::string& description, int health,
        const std::vector<std::shared_ptr<Attack>>& attacks);

  void TakeDamage(int damage);
  void Heal(int delta);

  int GetHealth() const;
  std::string GetName() const;
  std::vector<std::shared_ptr<Attack>> GetAttacks() const;

 private:
  int health_;
  std::string name_;
  std::string description_;
  std::vector<std::shared_ptr<Attack>> attacks_;
};

#endif  // ENEMY_H_
