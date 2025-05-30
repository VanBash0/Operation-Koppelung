#include "View.h"

View::View() {
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	player_win = newwin(5, 60, 0, 0);
	main_win = newwin(10, 60, 5, 0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
}

View::~View() {
	delwin(main_win);
	delwin(player_win);
}

void View::setOptions(const std::vector<std::string>& options_) {
	options = options_;
}

void View::drawMenu(int& selected, int& health, int& sanity) {
    wclear(main_win);
    box(main_win, 0, 0);
    for (int i = 0; i < options.size(); i++) {
        if (i == selected) wattron(main_win, A_REVERSE);
        mvwprintw(main_win, i + 1, 1, "%s", options[i].c_str());
        if (i == selected) wattroff(main_win, A_REVERSE);
    }
    wrefresh(main_win);
	showPlayerStats(health, sanity);
}

void View::drawProgressBar(WINDOW* win, int y, int x, const std::string& label, int value, int max_value, int width) {
    float percentage = (float)value / max_value;
    int filled_width = static_cast<int>(percentage * width);
    mvwprintw(win, y, x, "%s: ", label.c_str());
    for (int i = 0; i < filled_width; ++i) {
        waddch(win, ACS_CKBOARD);
    }
    for (int i = filled_width; i < width; ++i) {
        waddch(win, ACS_BOARD);
    }
}

void View::showPlayerStats(int health, int sanity) {
	wclear(player_win);
    box(player_win, 0, 0);
	mvwprintw(player_win, 1, 1, "%s", "Name: Aleksey Ryabinin");
    wattron(player_win, COLOR_PAIR(1));
    drawProgressBar(player_win, 2, 1, "Health", health, 100, 10);
    wattron(player_win, COLOR_PAIR(2));
    drawProgressBar(player_win, 3, 1, "Sanity", sanity, 100, 10);
    wattroff(player_win, COLOR_PAIR(2));
	wrefresh(player_win);
}

void View::showText(std::vector<std::string>& text) {
    wclear(main_win);
    box(main_win, 0, 0);
    for (int i = 0; i < text.size(); i++) {
		mvwprintw(main_win, i + 1, 1, "%s", text[i].c_str());
	}
    wrefresh(main_win);
}