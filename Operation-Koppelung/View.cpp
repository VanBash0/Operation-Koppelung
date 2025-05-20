#include "View.h"

View::View() {
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	player_win = newwin(4, 40, 0, 0);
	main_win = newwin(10, 40, 4, 0);
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
    box(main_win, 0, 0);
    for (int i = 0; i < options.size(); i++) {
        if (i == selected) wattron(main_win, A_REVERSE);
        mvwprintw(main_win, i + 1, 1, "%s", options[i].c_str()); // y=i+1
        if (i == selected) wattroff(main_win, A_REVERSE);
    }
    wrefresh(main_win);
	updatePlayerStats();
}

void View::updatePlayerStats() {
	wclear(player_win);
    box(player_win, 0, 0);
	mvwprintw(player_win, 1, 1, "%s", "Nu tut tipa statistica");
	mvwprintw(player_win, 2, 1, "%s", "da");
	wrefresh(player_win);
}