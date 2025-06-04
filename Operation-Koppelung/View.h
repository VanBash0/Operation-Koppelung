#ifndef VIEW_H_
#define VIEW_H_

#include <memory>
#include <string>
#include <vector>

#include "curses.h"

class View {
 public:
  View();
  ~View();

  // ������������� ������ ����� ��� ����
  void SetOptions(const std::vector<std::string>& options);

  // ������ ��������� ���������
  void DrawProgressBar(WINDOW* win, int y, int x, const std::string& label,
                       int value, int max_value, int width);

  // ������ ���� � ���������� ���������� ������ � ���������� ������
  void DrawMenu(int selected, int health, int sanity);

  // ���������� ���������� ������
  void ShowPlayerStats(int health, int sanity);

  // ���������� ����� � �������� ����
  void ShowText(const std::vector<std::string>& text);

 private:
  std::vector<std::string> options_;
  WINDOW* player_win_;
  WINDOW* main_win_;
};

#endif  // VIEW_H_
