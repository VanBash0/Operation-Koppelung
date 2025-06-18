#include "option_manager.h"

#include <fstream>

#include "json.hpp"
#include "option.h"

static const size_t kCacheSize = 50;

OptionManager::OptionManager() : options_(kCacheSize) {}

Option* OptionManager::GetOption(int id) {
  if (!options_.Get(id)) {
    AddOption(id);
  }
  return options_.Get(id);
}

void OptionManager::AddOption(int id) {
  if (options_.Contains(id)) {
    return;
  }

  std::ifstream file("options.json");

  nlohmann::json data = nlohmann::json::parse(file);

  for (const auto& option_data : data) {
    if (option_data["id"] != id) {
      continue;
    }

    std::string description = option_data["description"].get<std::string>();
    std::string story = option_data["story"].get<std::string>();
    std::string after_story = option_data["after_story"].get<std::string>();
    bool is_picked = option_data["isPicked"].get<bool>();
    std::string type_str = option_data["type"].get<std::string>();

    std::unique_ptr<Option> option;

    if (type_str == "kExploration") {
      int loot_id = option_data["loot_id"].get<int>();
      option = std::make_unique<ExplorationOption>(
          std::move(description), std::move(story), std::move(after_story),
          is_picked, loot_id);
    } else if (type_str == "kBattle") {
      std::vector<int> enemies_id =
          option_data["enemies_id"].get<std::vector<int>>();
      option = std::make_unique<BattleOption>(
          std::move(description), std::move(story), std::move(after_story),
          is_picked, enemies_id);
    } else if (type_str == "kGramophone") {
      int sanity_restore = option_data["sanity_restore"].get<int>();
      option = std::make_unique<GramophoneOption>(
          std::move(description), std::move(story), std::move(after_story),
          is_picked, sanity_restore);
    } else if (type_str == "kRoomChange") {
      int room_id = option_data["room_id"].get<int>();
      option = std::make_unique<RoomChangeOption>(
          std::move(description), std::move(story), std::move(after_story),
          is_picked, room_id);
    }

    if (option) {
      options_.Put(id, std::move(option));
    }

    break;
  }
}
