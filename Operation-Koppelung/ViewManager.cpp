#include <sstream>
#include <vector>
#include <curses.h>
#include "ViewManager.h"

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

std::vector<std::string> ViewManager::split(const std::string& line) {
	std::vector<std::string> split_line;
	std::istringstream iss(line);
	std::string str;

	while (std::getline(iss, str, ';')) {
		split_line.push_back(str);
	}
	return split_line;
}

void ViewManager::printText(std::string text) {
	std::vector<std::string> lines = split(text);
	view->showText(lines);
	waitUntilHitEnter();
}

void ViewManager::printTextByLine(std::string text) {
	std::vector<std::string> lines = split(text);
	for (int i = 0; i < lines.size(); i++) {
		std::vector<std::string> line = { lines[i] };
		view->showText(line);
		waitUntilHitEnter();
	}
}

void ViewManager::waitUntilHitEnter() {
	int key;
	while (true) {
		key = getch();
		if (key == 10 || key == 90 || key == 122) break;
	}
	handleInput(key);
}