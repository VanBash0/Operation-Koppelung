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
    void update();
    void takeDamage(int damage);
    int getDamage() const;
    std::vector<std::shared_ptr<Attack>> getSpells() const;
    int getDefence() const;
    int getHealth() const;
    int getSanity() const;
    std::string getWeaponName() const;
    int getLocation() const;
    void setLocation(const int& location);
    std::vector<std::shared_ptr<Item>> getItems() const;
    std::shared_ptr<Item> getWeapon() const;
    std::shared_ptr<Item> getArmor() const;
    std::shared_ptr<Item> getAmulet() const;
    void healHealth(int delta);
    void healSanity(int delta);
    void loseSanity(int delta);
private:
    int health, sanity, location;
    std::shared_ptr<Item> weapon, armor, amulet;
    std::vector<std::shared_ptr<Item>> inventory;
    std::vector<std::shared_ptr<Attack>> spells;
};