#include "Menu.h"
#include <curses.h>

Menu::Menu(const std::vector<std::string>& options_) : options(options_) {
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

Menu::~Menu() {
	endwin();
}

void Menu::draw() {
	clear();
	mvprintw(0, 0, "Choose your option:");
	for (int i = 0; i < options.size(); i++) {
		if (i == selected) attr_on(A_REVERSE, NULL);
		mvprintw(1 + i, 2, "%s", options[i].c_str());
		if (i == selected) attr_off(A_REVERSE, NULL);
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

int Menu::run() {
	while (true) {
		draw();
		int key = getch();

		if (key == 10) {
			return selected;
		}
		handleInput(key);
	}
}

void Menu::show() {
	int choice = run();
	mvprintw(10, 0, "Выбрано: %s", options[choice]);
	refresh();
	getch();
}