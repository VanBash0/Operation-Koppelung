#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>
#include <vector>

#include "attack_manager.h"
#include "item_manager.h"

class Player {
 public:
  Player(ItemManager* item_manager, AttackManager* attack_manager);

  void TakeDamage(int damage);
  void LoseSanity(int damage);
  void HealHealth(int delta);
  void HealSanity(int delta);

  void EquipWeapon(int inventory_index);
  void EquipArmor(int inventory_index);

  int GetDamage() const;
  int GetDefence() const;
  int GetHealth() const;
  int GetSanity() const;
  int GetLocation() const;
  std::string GetWeaponName() const;

  void SetLocation(int location);
  void SetDefaultStats();

  std::vector<Attack*> GetSpells() const;
  std::vector<Item*> GetItems() const;

  Item* GetWeapon() const;
  Item* GetArmor() const;

  bool InventoryFull() const;

  void AddItem(int item_id, ItemManager* item_manager);
  void RemoveItem(int item_id);

 private:
  int health_;
  int sanity_;
  int location_;
  int prev_location_;

  Item* weapon_ = nullptr;
  Item* armor_ = nullptr;

  std::vector<Item*> inventory_;
  std::vector<Attack*> spells_;
};

#endif  // PLAYER_H_
