#include "view.h"

View::View() {
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  player_win_ = newwin(5, 60, 0, 0);
  main_win_ = newwin(10, 60, 5, 0);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
}

View::~View() {
  delwin(main_win_);
  delwin(player_win_);
  endwin();
}

void View::SetOptions(const std::vector<std::string>& options) {
  options_ = options;
}

void View::DrawProgressBar(WINDOW* win, int y, int x, const std::string& label,
                           int value, int max_value, int width) {
  float percentage = static_cast<float>(value) / max_value;
  int filled_width = static_cast<int>(percentage * width);

  mvwprintw(win, y, x, "%s: ", label.c_str());
  for (int i = 0; i < filled_width; ++i) {
    waddch(win, ACS_CKBOARD);
  }
  for (int i = filled_width; i < width; ++i) {
    waddch(win, ACS_BOARD);
  }
}
void View::DrawMenu(int selected, int health, int sanity) {
  wclear(main_win_);
  box(main_win_, 0, 0);
  for (size_t i = 0; i < options_.size(); ++i) {
    if (static_cast<int>(i) == selected) wattron(main_win_, A_REVERSE);
    mvwprintw(main_win_, static_cast<int>(i) + 1, 1, "%s", options_[i].c_str());
    if (static_cast<int>(i) == selected) wattroff(main_win_, A_REVERSE);
  }
  wrefresh(main_win_);

  ShowPlayerStats(health, sanity);
}

void View::ShowPlayerStats(int health, int sanity) {
  wclear(player_win_);
  box(player_win_, 0, 0);

  mvwprintw(player_win_, 1, 1, "%s", "Name: Aleksey Ryabinin");

  wattron(player_win_, COLOR_PAIR(1));
  DrawProgressBar(player_win_, 2, 1, "Health", health, 100, 10);
  wattroff(player_win_, COLOR_PAIR(1));

  wattron(player_win_, COLOR_PAIR(2));
  DrawProgressBar(player_win_, 3, 1, "Sanity", sanity, 100, 10);
  wattroff(player_win_, COLOR_PAIR(2));

  wrefresh(player_win_);
}

void View::ShowText(const std::vector<std::string>& text) {
  wclear(main_win_);
  box(main_win_, 0, 0);
  for (size_t i = 0; i < text.size(); ++i) {
    mvwprintw(main_win_, static_cast<int>(i) + 1, 1, "%s", text[i].c_str());
  }
  wrefresh(main_win_);
}
