#ifndef ITEM_H_
#define ITEM_H_

#include <string>

enum class ItemType {
  kWeapon,
  kArmor,
  kHealthHealer,
  kSanityHealer,
  kInstantWeapon,
};

struct Item {
  int id;
  std::string name;
  std::string description;
  ItemType type;
  int value;
  Item(int id, const std::string& name, const std::string& description,
       ItemType type, int value)
      : id(id), name(name), description(description), type(type), value(value) {
        };
};

#endif  // ITEM_H_
