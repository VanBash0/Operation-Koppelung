#include "save_manager.h"

#include <fstream>

#include "json.hpp"

void SaveManager::ResetProgress() {
  ResetPlayer();
  ResetRooms();
  ResetOptions();
}

void SaveManager::ResetPlayer() {
  std::ifstream input_file("player.json");
  nlohmann::json player_data = nlohmann::json::parse(input_file);
  input_file.close();

  player_data[0]["health"] = 100;
  player_data[0]["sanity"] = 100;
  player_data[0]["location"] = 0;
  player_data[0]["items_id"].clear();
  player_data[0]["weapon_id"] = -1;
  player_data[0]["armor_id"] = -1;
  player_data[0]["spells_id"].clear();

  std::ofstream output_file("player.json");
  output_file << player_data.dump(2);
  output_file.close();
}

void SaveManager::ResetRooms() {
  std::ifstream input_file("rooms.json");
  nlohmann::json data = nlohmann::json::parse(input_file);
  input_file.close();

  for (auto& room : data) {
    room["room_entered"] = false;
  }

  std::ofstream output_file("rooms.json");
  output_file << data.dump(2);
  output_file.close();
}

void SaveManager::ResetOptions() {
  std::ifstream input_file("options.json");
  nlohmann::json data = nlohmann::json::parse(input_file);
  input_file.close();

  for (auto& option : data) {
    option["is_picked"] = false;
  }

  std::ofstream output_file("options.json");
  output_file << data.dump(2);
  output_file.close();
}

void SaveManager::SavePlayer(Player* player) {
  std::ifstream input_file("player.json");
  nlohmann::json player_data = nlohmann::json::parse(input_file);
  input_file.close();

  player_data[0]["health"] = player->GetHealth();
  player_data[0]["sanity"] = player->GetSanity();
  player_data[0]["location"] = player->GetLocation();

  player_data[0]["items_id"].clear();
  for (const auto& item : player->GetItems()) {
    player_data[0]["items_id"].push_back(item->id);
  }

  player_data[0]["weapon_id"] =
      player->GetWeapon() ? player->GetWeapon()->id : -1;
  player_data[0]["armor_id"] = player->GetArmor() ? player->GetArmor()->id : -1;

  player_data[0]["spells_id"].clear();
  for (const auto& spell : player->GetSpells()) {
    player_data[0]["spells_id"].push_back(spell->id);
  }

  std::ofstream output_file("player.json");
  output_file << player_data.dump(2);
  output_file.close();
}

void SaveManager::SaveRoomEntered(int id) {
  std::ifstream input_file("rooms.json");
  nlohmann::json data = nlohmann::json::parse(input_file);
  input_file.close();

  for (auto& room : data) {
    if (room["id"] == id) {
      room["room_entered"] = true;
      break;
    }
  }

  std::ofstream output_file("rooms.json");
  output_file << data.dump(2);
  output_file.close();
}

void SaveManager::SaveOptionPicked(int id) {
  std::ifstream input_file("options.json");
  nlohmann::json data = nlohmann::json::parse(input_file);
  input_file.close();

  for (auto& option : data) {
    if (option["id"] == id) {
      option["is_picked"] = true;
      break;
    }
  }

  std::ofstream output_file("options.json");
  output_file << data.dump(2);
  output_file.close();
}
