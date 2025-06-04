#include "player.h"

#include <fstream>

#include "json.hpp"

Player::Player(const std::shared_ptr<ItemManager>& item_manager,
               const std::shared_ptr<AttackManager>& attack_manager) {
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
  if (inventory_index < 0 ||
      inventory_index >= static_cast<int>(inventory_.size())) {
    return;
  }

  std::shared_ptr<Item> selected_item = inventory_[inventory_index];
  if (!selected_item || selected_item->type != ItemType::kWeapon) {
    return;
  }

  // Обмен текущего оружия с выбранным в инвентаре предметом
  std::swap(weapon_, inventory_[inventory_index]);
}

void Player::EquipArmor(int inventory_index) {
  if (inventory_index < 0 ||
      inventory_index >= static_cast<int>(inventory_.size())) {
    return;
  }

  std::shared_ptr<Item> selected_item = inventory_[inventory_index];
  if (!selected_item || selected_item->type != ItemType::kArmor) {
    return;
  }

  // Обмен текущей брони с выбранным в инвентаре предметом
  std::swap(armor_, inventory_[inventory_index]);
}

int Player::GetDamage() const { return weapon_ ? weapon_->value : 0; }

int Player::GetDefence() const { return armor_ ? armor_->value : 0; }

int Player::GetHealth() const { return health_; }

int Player::GetSanity() const { return sanity_; }

int Player::GetLocation() const { return location_; }

void Player::SetLocation(int location) { location_ = location; }

std::string Player::GetWeaponName() const {
  return weapon_ ? weapon_->name : "Unarmed";
}

std::vector<std::shared_ptr<Attack>> Player::GetSpells() const {
  return spells_;
}

std::vector<std::shared_ptr<Item>> Player::GetItems() const {
  return inventory_;
}

std::shared_ptr<Item> Player::GetWeapon() const { return weapon_; }

std::shared_ptr<Item> Player::GetArmor() const { return armor_; }

bool Player::InventoryFull() const { return inventory_.size() >= 8; }

void Player::AddItem(int item_id,
                     const std::shared_ptr<ItemManager>& item_manager) {
  if (!InventoryFull()) {
    inventory_.push_back(item_manager->GetItem(item_id));
  }
}

void Player::RemoveItem(int item_id) {
  auto it = std::remove_if(inventory_.begin(), inventory_.end(),
                           [item_id](const std::shared_ptr<Item>& item) {
                             return item->id == item_id;
                           });
  inventory_.erase(it, inventory_.end());
}

void Player::Update() {
  std::ifstream input_file("player.json");
  nlohmann::json player_data = nlohmann::json::parse(input_file);
  input_file.close();

  player_data[0]["health"] = health_;
  player_data[0]["sanity"] = sanity_;
  player_data[0]["location"] = location_;

  player_data[0]["items_id"].clear();
  for (const auto& item : inventory_) {
    player_data[0]["items_id"].push_back(item->id);
  }

  player_data[0]["weapon_id"] = weapon_ ? weapon_->id : -1;
  player_data[0]["armor_id"] = armor_ ? armor_->id : -1;

  player_data[0]["spells_id"].clear();
  for (const auto& spell : spells_) {
    player_data[0]["spells_id"].push_back(spell->id);
  }

  std::ofstream output_file("player.json");
  output_file << player_data.dump(4);
  output_file.close();
}
