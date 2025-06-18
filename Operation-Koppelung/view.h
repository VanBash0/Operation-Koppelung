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

  // Устанавливает список опций для меню
  void SetOptions(const std::vector<std::string>& options);

  // Рисует индикатор прогресса
  void DrawProgressBar(WINDOW* win, int y, int x, const std::string& label,
                       int value, int max_value, int width);

  // Рисует меню с подсветкой выбранного пункта и статистику игрока
  void DrawMenu(int selected, int health, int sanity);

  // Показывает статистику игрока
  void ShowPlayerStats(int health, int sanity);

  // Отображает текст в основном окне
  void ShowText(const std::vector<std::string>& text);

 private:
  std::vector<std::string> options_;
  WINDOW* player_win_;
  WINDOW* main_win_;
};

#endif  // VIEW_H_
