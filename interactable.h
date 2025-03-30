#pragma once
#include "entity.h"
#include "pch.h"
#include "player.h"
#include <memory>
#include <vector>

class Interactable : public virtual Entity {
public:
  explicit Interactable(const std::string &name = "Interactable")
      : Entity(name) {}
  virtual ~Interactable() = default;
  virtual void showInteractionUI(float, float);
  virtual void drawInteractionMenu(Player &);
  virtual void handleInteraction(Player &player,
                                 std::vector<std::shared_ptr<Entity>> &);
  virtual void handleInteraction(Player &player);
  bool isInteractionMenuShowing = true;
};
