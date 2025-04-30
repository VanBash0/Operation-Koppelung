#pragma once
#include <curses.h>
#include <vector>
#include <string>

class Menu {
public:
	Menu(const std::vector<std::string>& options_);
	~Menu();

	void show();
	int run();

private:
	std::vector<std::string> options;
	int selected = 0;

	void draw();
	void handleInput(int key);
};