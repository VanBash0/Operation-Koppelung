#pragma once
#include <memory>
#include "Option.h"
#include "LRUCache.h"

class OptionManager {
private:
	LRUCache<Option> options;
public:
	OptionManager();
	void addOption(int id);
	std::shared_ptr<Option> getOption(int id);
};