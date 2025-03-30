#pragma once
#include "entity.h"
#include "interactable.h"

class PlantPot : public virtual Entity, public Interactable {
private:
  bool hasBeenPlanted;

public:
  PlantPot();
  void handleInteraction(
      Player &player,
      std::vector<std::shared_ptr<Entity>> &entitesDrawnToWorld) override;
  void drawInteractionMenu(Player &) override;
};
