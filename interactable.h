#pragma once
#include "entity.h"
#include "player.h"
#include <memory>
#include <vector>

class Interactable : public virtual Entity {
public:
  explicit Interactable(const std::string &name = "Interactable")
      : Entity(name) {}
  virtual ~Interactable() = default;
  virtual void showInteractionUI(float, float);
  virtual void handleInteraction(Player &player,
                                 std::vector<std::shared_ptr<Entity>> &);
  bool isInteractable = true;
};
