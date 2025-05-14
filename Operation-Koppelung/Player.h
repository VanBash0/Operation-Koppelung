#pragma once
#include <vector>
#include <memory>
#include "Item.h"
#include "Attack.h"
#include "ItemManager.h"
#include "AttackManager.h"

class Player {
public:
    Player(ItemManager* itemManager, AttackManager* attackManager);
    void update();
private:
    int health, sanity;
    std::unique_ptr<Item> weapon, armor, amulet;
    std::vector<std::unique_ptr<Item>> inventory;
    std::vector<std::unique_ptr<Attack>> spells;
};