#ifndef ATTACK_MANAGER_H_
#define ATTACK_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "attack.h"

// �������� ����: ������ ����� �� �� ID
class AttackManager {
 public:
  explicit AttackManager();

  // ���������� ��������� �� ����� �� ID ��� nullptr, ���� �� �������
  Attack* GetAttack(int id) const;

 private:
  std::unordered_map<int, std::unique_ptr<Attack>> attacks_;
};

#endif  // ATTACK_MANAGER_H_
