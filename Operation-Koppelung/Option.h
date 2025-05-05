#pragma once
#include <string>

class Option {
public:
	Option(std::string description);
	//virtual void execute() = 0;
	void execute();
	std::string getDescription();

private:
	std::string description;
};