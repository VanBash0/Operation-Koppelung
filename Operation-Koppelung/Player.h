#pragma once
#include "Item.h"
#include "Attack.h"
#include <vector>
#include <memory>

class Player {
private:
    static Player* instance;
    Player(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id);
    int hp, sanity;
    std::unique_ptr<Item> weapon, armor, amulet;
    std::vector<std::unique_ptr<Item>> inventory;
    std::vector<std::unique_ptr<Attack>> unlocked_spells;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
public:
    static Player& getInstance();
    static void initialize(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id);
    int getDamage();
	int getDefence();
    int getHealth();
    void takeDamage(int damage);
    Attack& getSpell(size_t index) const;
	size_t getSpellCount() const;
};