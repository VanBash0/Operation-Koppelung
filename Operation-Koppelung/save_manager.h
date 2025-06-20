#ifndef SAVE_MANAGER_H_
#define SAVE_MANAGER_H_

#include "player.h"

class SaveManager {
 public:
  void ResetProgress();
  void SavePlayer(Player* player);
  void SaveRoomEntered(int id);
  void SaveOptionPicked(int id);

 private:
  void ResetPlayer();
  void ResetRooms();
  void ResetOptions();
};

#endif  // SAVE_MANAGER_H_
