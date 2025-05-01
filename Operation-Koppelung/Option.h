#pragma once
#include <string>

class Option {
public:
	Option(int id, const std::string& description);
	//virtual void execute() = 0;
	void execute();
	std::string getDescription();

private:
	int id;
	std::string description;
};