#include "Menu.h"
#include <curses.h>

Menu::Menu(const std::vector<std::string>& options) : options(options) {
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	WINDOW* menu_win = newwin(10, 20, 3, 0);
	wrefresh(menu_win);
}

Menu::~Menu() {
	delwin(menu_win);
}

void Menu::draw() {
	wclear(menu_win);
	mvwprintw(menu_win, 1, 1, "Choose your option:");
	for (int i = 0; i < options.size(); i++) {
		if (i == selected) wattr_on(menu_win, A_REVERSE, NULL);
		mvwprintw(menu_win, 1 + i, 1, "%s", options[i].c_str());
		if (i == selected) wattr_off(menu_win, A_REVERSE, NULL);
	}
	refresh();
}

void Menu::handleInput(int key) {
	switch (key) {
	case KEY_UP:
		selected = (selected - 1 + options.size()) % options.size();
		break;
	case KEY_DOWN:
		selected = (selected + 1) % options.size();
		break;
	}
}

void Menu::waitUntilHit() {
	int key;
	while (true) {
		key = getch();
		if (key == KEY_UP || key == KEY_DOWN) break;
	}
	handleInput(key);
}

int Menu::run() {
	while (true) {
		draw();
		int key = getch();
		if (key == 10 || key == 90 || key == 122) {
			return selected;
		}
		if (key == 88 || key == 120) {
			return -1;
		}
		handleInput(key);
	}
}

void Menu::show() {
	int choice = run();
	mvwprintw(menu_win, 10, 1, "Picked: %s", options[choice].c_str());
	wrefresh(menu_win);
	getch();
}