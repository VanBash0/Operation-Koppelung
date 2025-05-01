#include "Item.h"

Item::Item(int id, std::string name, std::string description, ItemType type, int value) : id(id), name(name), description(description), type(type), value(value) {}