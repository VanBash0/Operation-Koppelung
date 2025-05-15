#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include <memory>
#include "View.h"

class MenuManager {
public:
	MenuManager(std::shared_ptr<View> view);
	int run(const std::vector<std::string>& options_);
	void waitUntilHit();
private:
	std::shared_ptr<View> view;
	std::vector<std::string> options;
	int selected;
	void handleInput(int key);
};