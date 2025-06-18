// option_manager.h
#ifndef OPTION_MANAGER_H_
#define OPTION_MANAGER_H_

#include <memory>

#include "lru_cache.h"
#include "option.h"

class OptionManager {
 private:
  LRUCache<Option> options_;

 public:
  OptionManager();
  Option* GetOption(int id);
  void AddOption(int id);
};

#endif  // OPTION_MANAGER_H_
