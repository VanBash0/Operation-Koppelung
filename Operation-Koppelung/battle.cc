#include "battle.h"

#include <string>
#include <vector>

Battle::Battle(const std::vector<int>& enemies_id, EnemyManager* enemy_manager,
               Player* player, ViewManager* view_manager)
    : player_(player), view_manager_(view_manager), player_defence_(0) {
  for (int id : enemies_id) {
    enemies_.push_back(enemy_manager->GetEnemy(id));
  }
}

bool Battle::ExecuteBattle() {
  // Устанавливаем начальные параметры игрока
  view_manager_->UpdatePlayerStats(player_->GetHealth(), player_->GetSanity());
  bool is_player_turn_ = true;

  // Основной цикл боя
  while (!IsBattleOver()) {
    if (is_player_turn_) {
      std::vector<Attack*> spells = player_->GetSpells();
      std::vector<std::string> spell_names;
      for (const auto& spell : spells) {
        spell_names.push_back(spell->name);
      }

      PlayerTurn(spells, spell_names);
      is_player_turn_ = false;
    } else {
      EnemiesTurn();
      is_player_turn_ = true;
    }
  }

  if (player_->GetHealth() > 0) {
    view_manager_->PrintText("You won!");
    return true;
  } else {
    view_manager_->PrintText(
        "You are fainting...;Surprisingly, you find yourself alive in "
        "several... minutes? Hours? Doesn't really matter.");
    player_->SetDefaultStats();
    view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                     player_->GetSanity());
    return false;
  }
}

void Battle::PlayerTurn(const std::vector<Attack*>& spells,
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

void Battle::EnemiesTurn() {
  for (const auto& enemy : enemies_) {
    std::vector<Attack*> attacks = enemy->GetAttacks();
    if (attacks.empty()) continue;

    int attack_idx = rand() % attacks.size();
    Attack* attack = attacks[attack_idx];

    int damage = std::max(0, attack->damage - player_defence_);
    player_defence_ = std::max(0, player_defence_ - attack->damage);

    if (attack->is_damaging) {
      if (attack->is_physical) {
        player_->TakeDamage(damage);
        view_manager_->PrintText(enemy->GetName() + " attacks you with " +
                                 attack->name + " and deals you " +
                                 std::to_string(damage) + " damage!");
      } else {
        player_->LoseSanity(damage);
        view_manager_->PrintText(enemy->GetName() + " attacks you with " +
                                 attack->name + " and deals you " +
                                 std::to_string(damage) + " sanity damage!");
      }
    } else {
      enemy->Heal(attack->damage);
      view_manager_->PrintText(enemy->GetName() + " heals themselves with " +
                               attack->name + " and restores " +
                               std::to_string(attack->damage) + " health!");
    }

    view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                     player_->GetSanity());
  }
}

bool Battle::HandleAttack() {
  std::vector<std::string> enemy_names;
  for (const auto& enemy : enemies_) {
    enemy_names.push_back(enemy->GetName() +
                          ". Health: " + std::to_string(enemy->GetHealth()));
  }

  int target = view_manager_->Run(enemy_names);

  int damage = player_->GetDamage();
  enemies_[target]->TakeDamage(damage);

  view_manager_->PrintText("You attack " + enemies_[target]->GetName() +
                           " with " + player_->GetWeaponName() + " and deal " +
                           std::to_string(damage) + " damage!");

  return true;
}

bool Battle::HandleMagic(const std::vector<Attack*>& spells,
                         const std::vector<std::string>& spell_names) {
  while (true) {
    if (spells.empty()) {
      view_manager_->PrintText("You do not know any spells to cast!");
      return false;
    }
    int spell_choice = view_manager_->Run(spell_names);

    const auto& spell = spells[spell_choice];
    if (player_->GetSanity() < spell->sanity_cost) {
      view_manager_->PrintText("Not enough sanity for this spell!");
      continue;
    }

    if (spell->is_damaging) {
      std::vector<std::string> enemy_names;
      for (const auto& enemy : enemies_) {
        enemy_names.push_back(enemy->GetName() + ". Health: " +
                              std::to_string(enemy->GetHealth()));
      }
      int target = view_manager_->Run(enemy_names);

      enemies_[target]->TakeDamage(spell->damage);

      view_manager_->PrintText(
          "You attack " + enemies_[target]->GetName() + " with " + spell->name +
          " and deal " + std::to_string(spell->damage) + " damage!;You lose " +
          std::to_string(spell->sanity_cost) + " sanity!");
      player_->LoseSanity(spell->sanity_cost);
      view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                       player_->GetSanity());

    } else {
      player_->HealHealth(spell->damage);
      view_manager_->PrintText("You heal " + std::to_string(spell->damage) +
                               " health with " + spell->name + "!;You lose " +
                               std::to_string(spell->sanity_cost) + " sanity!");
      player_->LoseSanity(spell->sanity_cost);
      view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                       player_->GetSanity());
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

  Item* item = items[item_choice];
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
      view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                       player_->GetSanity());
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
      view_manager_->UpdatePlayerStats(player_->GetHealth(),
                                       player_->GetSanity());
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
