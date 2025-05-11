#pragma once
#include <curses.h>
#include <vector>
#include <string>

class Menu {
public:
	Menu(const std::vector<std::string>& options);
	~Menu();

	void show();
	void waitUntilHit();
	int run();

private:
	std::vector<std::string> options;
	WINDOW* menu_win;
	int selected = 0;

	void draw();
	void handleInput(int key);
};