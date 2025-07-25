#include "Game.h"

#include <iostream>

Game::Game() {
  save_manager_ = std::make_unique<SaveManager>();
  attack_manager_ = std::make_unique<AttackManager>();
  option_manager_ = std::make_unique<OptionManager>();
  enemy_manager_ = std::make_unique<EnemyManager>(attack_manager_.get());
  item_manager_ = std::make_unique<ItemManager>();
  view_manager_ = std::make_unique<ViewManager>();
  player_ =
      std::make_unique<Player>(item_manager_.get(), attack_manager_.get());
  room_manager_ = std::make_unique<RoomManager>(
      option_manager_.get(), view_manager_.get(), player_.get(),
      enemy_manager_.get(), item_manager_.get(), save_manager_.get());
}

void Game::Run() {
  ungetch('\n');
  view_manager_->WaitUntilHitEnter();
  while (true) {
    int choice = view_manager_->Run();
    switch (choice) {
      case 0:
        Play();
        break;
      case 1:
        view_manager_->PrintText(
            "Controls:;Z/Enter - Confirm;X - Cancel;Up/Down - Choose option;C "
            "- Inventory;Esc - Main Menu");
        break;
      case 2:
        save_manager_->ResetProgress();
        view_manager_->PrintText("Progress has been reset.");
        break;
      case 3:
        exit(0);
    }
  }
}

void Game::Play() {
  while (true) {
    int room_id = player_->GetLocation();
    if (!room_manager_->RoomProcess(room_id)) {
      break;
    }
    if (player_->GetLocation() == -1) {
      save_manager_->ResetProgress();
      exit(0);
    }
  }
}
