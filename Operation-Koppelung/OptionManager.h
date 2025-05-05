#pragma once
#include <unordered_map>
#include <memory>
#include "Option.h"

class OptionManager {
private:
	std::unordered_map<int, std::shared_ptr<Option>> options;
public:
	void addOption(int id);
	std::shared_ptr<Option> getOption(int id);
	void checkFullness();
};