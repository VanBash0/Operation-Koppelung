#include "ViewManager.h"
#include <curses.h>

ViewManager::ViewManager(std::shared_ptr<View> view) : view(view) {};

void ViewManager::handleInput(int key) {
	switch (key) {
	case KEY_UP:
		selected = (selected - 1 + options.size()) % options.size();
		break;
	case KEY_DOWN:
		selected = (selected + 1) % options.size();
		break;
	}
}

int ViewManager::run(const std::vector<std::string>& options_) {
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

void ViewManager::waitUntilHit() {
	int key;
	while (true) {
		key = getch();
		if (key == KEY_UP || key == KEY_DOWN  || key == 10 || key == 90 || key == 122) break;
	}
	handleInput(key);
}

void ViewManager::printText(std::string text) {
	view->showText(text);
	waitUntilHitEnter();
}

void ViewManager::waitUntilHitEnter() {
	int key;
	while (true) {
		key = getch();
		if (key == 10 || key == 90 || key == 122) break;
	}
	handleInput(key);
}