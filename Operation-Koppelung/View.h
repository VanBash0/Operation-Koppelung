#pragma once
#include <vector>
#include <string>
#include <memory>
#include "curses.h"

class View {
public:
	View();
	~View();
	void drawMenu(int& selected);
	void setOptions(const std::vector<std::string>& options);
private:
	std::vector<std::string> options;
	WINDOW* player_win;
	WINDOW* main_win;
};