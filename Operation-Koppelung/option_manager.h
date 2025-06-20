// option_manager.h
#ifndef OPTION_MANAGER_H_
#define OPTION_MANAGER_H_

#include <memory>

#include "lru_cache.h"
#include "option.h"

class OptionManager {
 public:
  OptionManager();
  Option* GetOption(int id);
  void AddOption(int id);

 private:
  LRUCache<Option> options_;
};

#endif  // OPTION_MANAGER_H_
