#pragma once

#include "interactable.h"
#include "inventory.h"
#include <memory>
#include <vector>
class UserInterface {
public:
  static float scrollOffset;
  static void DrawMenu(std::vector<std::shared_ptr<Interactable>> &,
                       std::string);
};
