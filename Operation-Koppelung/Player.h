#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>
#include <vector>

#include "attack_manager.h"
#include "item_manager.h"

class Player {
 public:
  Player(const std::shared_ptr<ItemManager>& item_manager,
         const std::shared_ptr<AttackManager>& attack_manager);

  void Update();

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

  void SetLocation(int location);

  std::string GetWeaponName() const;

  std::vector<std::shared_ptr<Attack>> GetSpells() const;
  std::vector<std::shared_ptr<Item>> GetItems() const;

  std::shared_ptr<Item> GetWeapon() const;
  std::shared_ptr<Item> GetArmor() const;

  bool InventoryFull() const;

  void AddItem(int item_id, const std::shared_ptr<ItemManager>& item_manager);
  void RemoveItem(int item_id);

 private:
  int health_ = 100;
  int sanity_ = 100;
  int location_ = 0;

  std::shared_ptr<Item> weapon_ = nullptr;
  std::shared_ptr<Item> armor_ = nullptr;

  std::vector<std::shared_ptr<Item>> inventory_;
  std::vector<std::shared_ptr<Attack>> spells_;
};

#endif  // PLAYER_H_
