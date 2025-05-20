#pragma once
#include <vector>
#include <memory>
#include "Item.h"
#include "Attack.h"
#include "ItemManager.h"
#include "AttackManager.h"

class Player {
public:
    Player(std::shared_ptr<ItemManager> itemManager, std::shared_ptr<AttackManager> attackManager);
    //void update();
    void takeDamage(int damage);
    int getDamage() const;
    std::vector<std::shared_ptr<Attack>> getSpells() const;
    int getDefence() const;
    int getHealth() const;
    int getSanity() const;
private:
    int health, sanity;
    std::unique_ptr<Item> weapon, armor, amulet;
    std::vector<std::shared_ptr<Item>> inventory;
    std::vector<std::shared_ptr<Attack>> spells;
};