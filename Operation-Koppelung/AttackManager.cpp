#include <fstream>
#include "json.hpp"
#include "AttackManager.h"

AttackManager::AttackManager() {
	std::ifstream file("attacks.json");
	nlohmann::json data = nlohmann::json::parse(file);

	for (const auto& attackData : data) {
		int id = attackData["id"];
		attacks[id] = std::make_unique<Attack>(
			attackData["id"].get<int>(),
			attackData["damage"].get<int>(),
			attackData["sanity_cost"].get<int>(),
			attackData["name"].get<std::string>(),
			attackData["description"].get<std::string>(),
			attackData["is_physical"].get<bool>(),
			attackData["is_damaging"].get<bool>());
	}
}

const std::shared_ptr<Attack> AttackManager::getAttack(int id) const {
	return std::make_shared<Attack>(*attacks.at(id));
}