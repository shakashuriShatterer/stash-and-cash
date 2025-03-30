#pragma once
#include "entity.h"
#include "inventory.h"
#include <memory>
#include <vector>

class Player : public Entity {
private:
  bool canMove;
  int movementSpeed;

public:
  Inventory inventory;
  void move();
  void interact();
  void buyWeed();
  // setters
  void setCanMove(bool move);

  // getters
  bool getCanMove() const;
  int getMovementSpeed() const;

  Player();
};
