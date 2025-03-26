#pragma once
#include "entity.h"
#include "pch.h"
#include <memory>
#include <vector>

class Interactable;

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
    std::vector<std::shared_ptr<Interactable>> itemInventoryVector;
    std::vector<std::shared_ptr<Ganja>> weedInventoryVector;
    void drawInventoryMenu();
    void drawWeedSelection();
    std::shared_ptr<Ganja> GetSelectedWeed();
    void scrollInventoryMenu();
    void dragItem(std::vector<std::shared_ptr<Interactable>> &);
  };
  Inventory inventory;
};
