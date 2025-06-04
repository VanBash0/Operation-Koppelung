#include "battle.h"

#include <string>
#include <vector>

Battle::Battle(std::shared_ptr<Player> player,
               std::vector<std::shared_ptr<Enemy>> enemies,
               std::shared_ptr<ViewManager> view_manager)
    : player_(std::move(player)),
      enemies_(std::move(enemies)),
      view_manager_(std::move(view_manager)),
      player_defence_(0) {}

void Battle::PlayerTurn(const std::vector<std::shared_ptr<Attack>>& spells,
                        const std::vector<std::string>& spell_names) {
  const std::vector<std::string> kActions = {"Attack", "Magic", "Defend",
                                             "Item"};
  int actions_performed = 0;

  while (actions_performed < 2) {
    int choice = view_manager_->Run(kActions);
    switch (choice) {
      case 0:  // Атака
        if (HandleAttack()) {
          ++actions_performed;
        }
        break;
      case 1:  // Магия
        if (HandleMagic(spells, spell_names)) {
          ++actions_performed;
        }
        break;
      case 2:  // Защита
        HandleDefend();
        ++actions_performed;
        break;
      case 3:  // Предмет
        if (HandleItem()) {
          ++actions_performed;
        }
        break;
      default:
        // Некорректный выбор, повторяем
        break;
    }

    RemoveDeadEnemies();

    if (IsBattleOver()) {
      break;
    }
  }
}

bool Battle::HandleAttack() {
  std::vector<std::string> enemy_names;
  for (const auto& enemy : enemies_) {
    enemy_names.push_back(enemy->GetName() +
                          " HP: " + std::to_string(enemy->GetHealth()));
  }

  int target = view_manager_->Run(enemy_names);
  if (target < 0 || target >= static_cast<int>(enemies_.size())) {
    return false;
  }

  int damage = player_->GetDamage();
  enemies_[target]->TakeDamage(damage);

  view_manager_->PrintText("You attack " + enemies_[target]->GetName() +
                           " with " + player_->GetWeaponName() + " and deal " +
                           std::to_string(damage) + " damage!");

  return true;
}

bool Battle::HandleMagic(const std::vector<std::shared_ptr<Attack>>& spells,
                         const std::vector<std::string>& spell_names) {
  while (true) {
    int spell_choice = view_manager_->Run(spell_names);
    if (spell_choice < 0 || spell_choice >= static_cast<int>(spells.size())) {
      return false;
    }

    const auto& spell = spells[spell_choice];
    if (player_->GetSanity() < spell->sanity_cost) {
      view_manager_->PrintText("Not enough sanity for this spell!");
      continue;
    }

    if (spell->is_damaging) {
      std::vector<std::string> enemy_names;
      for (const auto& enemy : enemies_) {
        enemy_names.push_back(enemy->GetName() +
                              " HP: " + std::to_string(enemy->GetHealth()));
      }
      int target = view_manager_->Run(enemy_names);
      if (target < 0 || target >= static_cast<int>(enemies_.size())) {
        return false;
      }

      enemies_[target]->TakeDamage(spell->damage);

      view_manager_->PrintText(
          "You attack " + enemies_[target]->GetName() + " with " + spell->name +
          " and deal " + std::to_string(spell->damage) + " damage!;You lose " +
          std::to_string(spell->sanity_cost) + " sanity!");
      player_->LoseSanity(spell->sanity_cost);
      view_manager_->SetPlayerSanity(player_->GetSanity());
      view_manager_->UpdatePlayerStats();

    } else {
      player_->HealHealth(spell->damage);
      view_manager_->PrintText("You heal " + std::to_string(spell->damage) +
                               " health with " + spell->name + "!;You lose " +
                               std::to_string(spell->sanity_cost) + " sanity!");
      player_->LoseSanity(spell->sanity_cost);
      view_manager_->SetPlayerSanity(player_->GetSanity());
      view_manager_->SetPlayerHealth(player_->GetHealth());
      view_manager_->UpdatePlayerStats();
    }

    return true;
  }
}

void Battle::HandleDefend() {
  int delta = player_->GetHealth() / 10;
  player_defence_ += delta;

  view_manager_->PrintText("You make a defensive pose. Your defence rises by " +
                           std::to_string(delta) + "!");
}

bool Battle::HandleItem() {
  const auto& items = player_->GetItems();
  if (items.empty()) {
    view_manager_->PrintText("You have no items to use.");
    return false;
  }

  std::vector<std::string> item_names;
  for (const auto& item : items) {
    item_names.push_back(item->name);
  }

  int item_choice = view_manager_->Run(item_names);
  if (item_choice < 0 || item_choice >= static_cast<int>(items.size())) {
    return false;
  }

  const std::shared_ptr<Item>& item = items[item_choice];
  switch (item->type) {
    case ItemType::kWeapon:
      view_manager_->PrintText("You equip " + item->name + "!");
      player_->EquipWeapon(item->id);
      break;
    case ItemType::kArmor:
      view_manager_->PrintText("You equip " + item->name + "!");
      player_->EquipArmor(item->id);
      break;
    case ItemType::kHealthHealer:
      player_->HealHealth(item->value);
      if (player_->GetHealth() == 100) {
        view_manager_->PrintText("You use " + item->name +
                                 " and fully restore your health!");
      } else {
        view_manager_->PrintText("You use " + item->name + " and heal " +
                                 std::to_string(item->value) + " health!");
      }
      player_->RemoveItem(item->id);
      view_manager_->SetPlayerHealth(player_->GetHealth());
      view_manager_->UpdatePlayerStats();
      break;
    case ItemType::kSanityHealer:
      player_->HealSanity(item->value);
      if (player_->GetSanity() == 100) {
        view_manager_->PrintText("You use " + item->name +
                                 " and fully restore your sanity!");
      } else {
        view_manager_->PrintText("You use " + item->name + " and heal " +
                                 std::to_string(item->value) + " sanity!");
      }
      player_->RemoveItem(item->id);
      view_manager_->SetPlayerSanity(player_->GetSanity());
      view_manager_->UpdatePlayerStats();
      break;
    case ItemType::kInstantWeapon:
      for (auto& enemy : enemies_) {
        enemy->TakeDamage(item->value);
      }
      view_manager_->PrintText("You use " + item->name + " and deal " +
                               std::to_string(item->value) +
                               " damage to all enemies!");
      player_->RemoveItem(item->id);
      break;
    default:
      view_manager_->PrintText("Unknown item type.");
      return false;
  }

  return true;
}

void Battle::RemoveDeadEnemies() {
  for (auto it = enemies_.begin(); it != enemies_.end();) {
    if ((*it)->GetHealth() <= 0) {
      view_manager_->PrintText("You kill " + (*it)->GetName() + "!");
      it = enemies_.erase(it);
    } else {
      ++it;
    }
  }
}

bool Battle::IsBattleOver() const {
  return enemies_.empty() || player_->GetHealth() <= 0;
}
