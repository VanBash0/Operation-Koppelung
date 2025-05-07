#pragma once
#include <string>

enum OptionType {
	EXPLORATION,
	BATTLE,
	GRAMMOPHONE,
	ROOMCHANGE,
};

class Option {
public:
	Option(std::string description, OptionType type);
	std::string getDescription();

private:
	std::string description;
	OptionType type;
};