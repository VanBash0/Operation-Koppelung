#ifndef ROOM_H_
#define ROOM_H_

#include <vector>

struct Room {
  Room(const std::vector<int>& options_id, const std::vector<int>& enemies_id,
       bool room_entered)
      : options_id_(options_id),
        enemies_id_(enemies_id),
        room_entered_(room_entered) {}

  std::vector<int> options_id_;
  std::vector<int> enemies_id_;
  bool room_entered_;
};

#endif  // ROOM_H_
