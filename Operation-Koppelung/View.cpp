#include "View.h"

View::View() {
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	player_win = newwin(2, 20, 0, 0);
	main_win = newwin(10, 20, 3, 0);
}

View::~View() {
	delwin(main_win);
	delwin(player_win);
}

void View::setOptions(const std::vector<std::string>& options_) {
	options = options_;
}

void View::drawMenu(int& selected) {
	wclear(main_win);
	for (int i = 0; i < options.size(); i++) {
		if (i == selected) wattr_on(main_win, A_REVERSE, NULL);
		mvwprintw(main_win, 1 + i, 1, "%s", options[i].c_str());
		if (i == selected) wattr_off(main_win, A_REVERSE, NULL);
	}
	refresh();
}