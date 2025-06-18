#include "view_manager.h"

#include <sstream>

ViewManager::ViewManager(View* view) : view_(view) {}

int ViewManager::Run(const std::vector<std::string>& options) {
  options_ = options;
  view_->SetOptions(options_);
  selected_ = 0;
  while (true) {
    view_->DrawMenu(selected_, player_health_, player_sanity_);
    int key = getch();
    if (key == 10 || key == 90 || key == 122) {  // Enter или 'Z'/'z'
      return selected_;
    }
    if (key == 88 || key == 120) {  // 'X'/'x'
      return -1;
    }
    HandleInput(key);
  }
}

void ViewManager::WaitUntilHit() {
  int key;
  while (true) {
    key = getch();
    if (key == KEY_UP || key == KEY_DOWN || key == 10 || key == 90 ||
        key == 122)
      break;
  }
  HandleInput(key);
}

void ViewManager::WaitUntilHitEnter() {
  int key;
  while (true) {
    key = getch();
    if (key == 10 || key == 90 || key == 122)  // Enter или 'Z'/'z'
      break;
  }
  HandleInput(key);
}

void ViewManager::PrintText(const std::string& text) {
  std::vector<std::string> lines = Split(text);
  view_->ShowText(lines);
  WaitUntilHitEnter();
}

void ViewManager::PrintTextByLine(const std::string& text) {
  std::vector<std::string> lines = Split(text);
  for (const auto& line : lines) {
    view_->ShowText(std::vector<std::string>{line});
    WaitUntilHitEnter();
  }
}

std::vector<std::string> ViewManager::Split(const std::string& line) {
  std::vector<std::string> split_line;
  std::istringstream iss(line);
  std::string str;

  while (std::getline(iss, str, ';')) {
    split_line.push_back(str);
  }
  return split_line;
}

void ViewManager::HandleInput(int key) {
  switch (key) {
    case KEY_UP:
      selected_ = (selected_ - 1 + options_.size()) % options_.size();
      break;
    case KEY_DOWN:
      selected_ = (selected_ + 1) % options_.size();
      break;
  }
}
