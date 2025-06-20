#include "player.h"

#include <fstream>

#include "json.hpp"

Player::Player(ItemManager* item_manager, AttackManager* attack_manager) {
  std::ifstream file("player.json");
  nlohmann::json data = nlohmann::json::parse(file);

  health_ = data[0]["health"].get<int>();
  sanity_ = data[0]["sanity"].get<int>();
  location_ = data[0]["location"].get<int>();

  for (int id : data[0]["items_id"]) {
    inventory_.push_back(item_manager->GetItem(id));
  }

  int weapon_id = data[0]["weapon_id"].get<int>();
  weapon_ = (weapon_id == -1) ? nullptr : item_manager->GetItem(weapon_id);

  int armor_id = data[0]["armor_id"].get<int>();
  armor_ = (armor_id == -1) ? nullptr : item_manager->GetItem(armor_id);

  for (int id : data[0]["spells_id"]) {
    spells_.push_back(attack_manager->GetAttack(id));
  }
}

void Player::TakeDamage(int damage) { health_ = std::max(0, health_ - damage); }

void Player::LoseSanity(int damage) { sanity_ = std::max(0, sanity_ - damage); }

void Player::HealHealth(int delta) { health_ = std::min(100, health_ + delta); }

void Player::HealSanity(int delta) { sanity_ = std::min(100, sanity_ + delta); }

void Player::EquipWeapon(int inventory_index) {
  // Обмен текущего оружия с выбранным в инвентаре предметом
  if (!weapon_) {
    weapon_ = inventory_[inventory_index];
    RemoveItem(inventory_[inventory_index]->id);
  } else {
    std::swap(weapon_, inventory_[inventory_index]);
  }
}

void Player::EquipArmor(int inventory_index) {
  // Обмен текущей брони с выбранным в инвентаре предметом
  if (!armor_) {
    armor_ = inventory_[inventory_index];
    RemoveItem(inventory_[inventory_index]->id);
  } else {
    std::swap(armor_, inventory_[inventory_index]);
  }
}

int Player::GetDamage() const { return weapon_ ? weapon_->value : 5; }

int Player::GetDefence() const { return armor_ ? armor_->value : 0; }

int Player::GetHealth() const { return health_; }

int Player::GetSanity() const { return sanity_; }

int Player::GetLocation() const { return location_; }

void Player::SetLocation(int location) {
  prev_location_ = location_;
  location_ = location;
}

void Player::SetDefaultStats() {
  health_ = 50;
  sanity_ = 50;
  location_ = prev_location_;
}

std::string Player::GetWeaponName() const {
  return weapon_ ? weapon_->name : "bare hands";
}

std::vector<Attack*> Player::GetSpells() const { return spells_; }

std::vector<Item*> Player::GetItems() const { return inventory_; }

Item* Player::GetWeapon() const { return weapon_; }

Item* Player::GetArmor() const { return armor_; }

bool Player::InventoryFull() const { return inventory_.size() >= 8; }

void Player::AddItem(int item_id, ItemManager* item_manager) {
  if (!InventoryFull()) {
    inventory_.push_back(item_manager->GetItem(item_id));
  }
}

void Player::RemoveItem(int item_id) {
  auto it =
      std::remove_if(inventory_.begin(), inventory_.end(),
                     [item_id](Item* item) { return item->id == item_id; });
  inventory_.erase(it, inventory_.end());
}
