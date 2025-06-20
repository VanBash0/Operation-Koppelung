#include "view.h"

#include <thread>

namespace {
constexpr unsigned int char_delay_ms = 30;
constexpr unsigned int line_delay_ms = 100;

constexpr int kExtraWinHeight = 5;
constexpr int kMainWinHeight = 10;
constexpr int kScreenWidth = 80;

constexpr int kExtraWinStartY = 0;
constexpr int kExtraWinStartX = 0;

constexpr int kMainWinStartY = kExtraWinHeight;
constexpr int kMainWinStartX = 0;
}  // namespace

View::View() {
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  extra_win_ =
      newwin(kExtraWinHeight, kScreenWidth, kExtraWinStartY, kExtraWinStartX);
  main_win_ =
      newwin(kMainWinHeight, kScreenWidth, kMainWinStartY, kMainWinStartX);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
}

View::~View() {
  delwin(main_win_);
  delwin(extra_win_);
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

void View::DrawMenu(int selected) {
  wclear(main_win_);
  box(main_win_, 0, 0);
  for (size_t i = 0; i < options_.size(); ++i) {
    if (static_cast<int>(i) == selected) wattron(main_win_, A_REVERSE);
    mvwprintw(main_win_, static_cast<int>(i) + 1, 1, "%s", options_[i].c_str());
    if (static_cast<int>(i) == selected) wattroff(main_win_, A_REVERSE);
  }
  wrefresh(main_win_);

  ShowTitle();
}

void View::ShowPlayerStats(int health, int sanity) {
  wclear(extra_win_);
  box(extra_win_, 0, 0);

  mvwprintw(extra_win_, 1, 1, "%s", "Name: Aleksey Ryabinin");

  wattron(extra_win_, COLOR_PAIR(1));
  DrawProgressBar(extra_win_, 2, 1, "Health", health, 100, 10);
  wattroff(extra_win_, COLOR_PAIR(1));

  wattron(extra_win_, COLOR_PAIR(2));
  DrawProgressBar(extra_win_, 3, 1, "Sanity", sanity, 100, 10);
  wattroff(extra_win_, COLOR_PAIR(2));

  wrefresh(extra_win_);
}

void View::ShowText(const std::vector<std::string>& text) {
  wclear(main_win_);
  box(main_win_, 0, 0);
  wrefresh(main_win_);

  for (size_t i = 0; i < text.size(); ++i) {
    for (size_t j = 0; j < text[i].size(); ++j) {
      mvwaddch(main_win_, i + 1, j + 1, text[i][j]);
      wrefresh(main_win_);
      std::this_thread::sleep_for(std::chrono::milliseconds(char_delay_ms));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(line_delay_ms));
  }
}

void View::ShowTitle() {
  wclear(extra_win_);
  box(extra_win_, 0, 0);
  mvwprintw(extra_win_, 1, 1, "%s", "~~~~~~~~~~~~~~~~~~~");
  mvwprintw(extra_win_, 2, 1, "%s", "OPERATION KOPPELUNG");
  mvwprintw(extra_win_, 3, 1, "%s", "~~~~~~~~~~~~~~~~~~~");
  wrefresh(extra_win_);
}
