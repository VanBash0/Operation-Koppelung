#include "enemy.h"

Enemy::Enemy(const std::string& name, const std::string& description,
             int health, const std::vector<Attack*>& attacks)
    : name_(name),
      description_(description),
      health_(health),
      attacks_(attacks) {}

void Enemy::TakeDamage(int damage) {
  health_ = (health_ < damage) ? 0 : health_ - damage;
}

void Enemy::Heal(int delta) { health_ += delta; }

std::string Enemy::GetName() const { return name_; }

int Enemy::GetHealth() const { return health_; }

std::vector<Attack*> Enemy::GetAttacks() const { return attacks_; }
