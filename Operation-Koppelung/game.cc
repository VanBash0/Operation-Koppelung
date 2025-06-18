#include "Game.h"

Game::Game() {
  attack_manager_ = std::make_unique<AttackManager>();
  option_manager_ = std::make_unique<OptionManager>();
  enemy_manager_ = std::make_unique<EnemyManager>(attack_manager_.get());
  item_manager_ = std::make_unique<ItemManager>();
  view_ = std::make_unique<View>();
  view_manager_ = std::make_unique<ViewManager>(view_.get());
  player_ =
      std::make_unique<Player>(item_manager_.get(), attack_manager_.get());
  room_manager_ = std::make_unique<RoomManager>(
      option_manager_.get(), view_manager_.get(), player_.get(),
      enemy_manager_.get(), item_manager_.get());
}

void Game::Play() {
  while (true) {
    int room_id = player_->GetLocation();
    room_manager_->RoomProcess(room_id);
  }
}
