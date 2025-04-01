#pragma once
#include "entity.h"
// #include "interactable.h"
// #include "interactable.h"
class Interactable;

struct Inventory {
  bool isInventoryShowing = false;
  bool isWeedInventoryShowing = false;
  std::vector<std::shared_ptr<Interactable>> itemInventoryVector;
  std::vector<std::shared_ptr<Interactable>> weedInventoryVector;
  void drawInventoryMenu();
  std::shared_ptr<Entity> GetSelectedWeed();
  std::shared_ptr<Interactable> GetSelectedItem();
  void scrollInventoryMenu();
  void dragItem(std::vector<std::shared_ptr<Interactable>> &);
};
