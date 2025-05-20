#include "MenuManager.h"
#include <curses.h>

MenuManager::MenuManager(std::shared_ptr<View> view) : view(view) {};

void MenuManager::handleInput(int key) {
	switch (key) {
	case KEY_UP:
		selected = (selected - 1 + options.size()) % options.size();
		break;
	case KEY_DOWN:
		selected = (selected + 1) % options.size();
		break;
	}
}

int MenuManager::run(const std::vector<std::string>& options_) {
	options = options_;
	view->setOptions(options);
	selected = 0;
	while (true) {
		view->drawMenu(selected, player_health, player_sanity);
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

void MenuManager::waitUntilHit() {
	int key;
	while (true) {
		key = getch();
		if (key == KEY_UP || key == KEY_DOWN  || key == 10 || key == 90 || key == 122) break;
	}
	handleInput(key);
}