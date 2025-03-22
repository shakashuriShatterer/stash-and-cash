#pragma once
#include "entity.h"
#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

class Player : public Entity {
private:
  bool canMove;
  int movementSpeed;

public:
  void move();
  void interact();
  void buyWeed();
  // setters
  void setCanMove(bool move);

  // getters
  bool getCanMove() const;
  int getMovementSpeed() const;

  Player();

  struct Inventory {
    bool isInventoryShowing = false;
    bool isWeedInventoryShowing = false;
    float scrollOffset = 5;
    std::vector<std::shared_ptr<Entity>> itemInventoryVector;
    std::vector<std::shared_ptr<Entity>> weedInventoryVector;
    void drawInventoryMenu();
    void drawWeedInventory(std::shared_ptr<Entity> &,
                           std::vector<std::shared_ptr<Entity>> &);
    void scrollInventoryMenu();
    void dragItem(std::vector<std::shared_ptr<Entity>> &);
  };
  Inventory inventory;
};
