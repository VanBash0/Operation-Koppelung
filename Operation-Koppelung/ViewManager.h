#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include <memory>
#include "View.h"

class ViewManager {
public:
	ViewManager(std::shared_ptr<View> view);
	int run(const std::vector<std::string>& options_);
	void waitUntilHit();
	void setPlayerHealth(int health) { player_health = health; };
	void setPlayerSanity(int sanity) { player_sanity = sanity; };
	void printText(std::string text);
	void updatePlayerStats() { view->showPlayerStats(player_health, player_sanity); };
private:
	std::shared_ptr<View> view;
	std::vector<std::string> options;
	int selected;
	int player_health;
	int player_sanity;
	void handleInput(int key);
};