#include "Player.h"

Player::Player(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id) : 
    hp(hp), 
    sanity(sanity), 
    weapon(items_id.empty() || items_id[0] == -1 ? nullptr : std::make_unique<Item>(items_id[0])), 
    armor(items_id.size() < 2 || items_id[1] == -1 ? nullptr : std::make_unique<Item>(items_id[1])), 
    amulet(items_id.size() < 3 || items_id[2] == -1 ? nullptr : std::make_unique<Item>(items_id[2])) 
{
    for (auto i = 3; i < items_id.size(); ++i) {
        if (items_id[i] != -1) {
            inventory.push_back(std::make_unique<Item>(items_id[i]));
        }
    }

	for (auto i = 0; i < attacks_id.size(); ++i) {
		unlocked_spells.push_back(std::make_unique<Attack>(attacks_id[i]));
	}
}