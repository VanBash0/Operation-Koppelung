#ifndef VIEW_MANAGER_H_
#define VIEW_MANAGER_H_

#include <curses.h>

#include <memory>
#include <string>
#include <vector>

#include "view.h"

class ViewManager {
 public:
  ViewManager();

  // ��������� ���� � ��������� �������.
  // ���������� ������ ���������� ������, -1 ��� ������ � -2 ��� ������
  int Run(const std::vector<std::string>& options);

  int Run();

  // ��� ������� �������, ������������ ������� � Enter/Z
  void WaitUntilHit();

  // ��� ������� ������� Enter ��� Z
  void WaitUntilHitEnter();

  void SetPlayerHealth(int health) { player_health_ = health; }
  void SetPlayerSanity(int sanity) { player_sanity_ = sanity; }
  void PrintText(const std::string& text);
  void PrintTextByLine(const std::string& text);
  void UpdatePlayerStats() {
    view_->ShowPlayerStats(player_health_, player_sanity_);
  }
  std::vector<std::string> Split(const std::string& line);

 private:
  void HandleInput(int key);

  std::unique_ptr<View> view_;
  std::vector<std::string> options_;
  int selected_ = 0;
  int player_health_ = 0;
  int player_sanity_ = 0;
};

#endif  // VIEW_MANAGER_H_
