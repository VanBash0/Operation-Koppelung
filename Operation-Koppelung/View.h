#pragma once
#include <vector>
#include <string>
#include <memory>
#include "curses.h"

class View {
public:
	View();
	~View();
	void drawMenu(int& selected, int& health, int& sanity);
	void setOptions(const std::vector<std::string>& options);
	void showPlayerStats(int health, int sanity);
	void drawProgressBar(WINDOW* win, int y, int x, const std::string& label, int value, int max_value, int width);
	void showText(std::vector<std::string>& text);
private:
	std::vector<std::string> options;
	WINDOW* player_win;
	WINDOW* main_win;
};