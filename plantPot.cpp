// clang-format off
#include "pch.h"
#include "plantPot.h"
#include "entity.h"
#include "interactable.h"
#include "player.h"
#include "userInterface.h"
// clang-format on
PlantPot::PlantPot()
    : Entity("plantPot"), Interactable(), hasBeenPlanted(false) {
  hasBeenPlanted = false;
  setTexture(LoadTexture("plant_pot.png"));
  setInventoryPosition({20, 10});
  setTextureSize(50, 50);
}

void PlantPot::handleInteraction(
    Player &player,
    std::vector<std::shared_ptr<Entity>> &entitiesDrawnToWorld) {
  auto weed = player.inventory.GetSelectedWeed();
  if (weed) {
    weed->setPosition({getPositionX(), getPositionY() - getTextureHeight()});
    entitiesDrawnToWorld.push_back(weed);
    std::cerr << "removing weedId: " << weed->getId() - 2;
    player.inventory.weedInventoryVector.erase(
        player.inventory.weedInventoryVector.begin() + (weed->getId() - 2));
  }
}

void PlantPot::drawInteractionMenu(Player &player) {
  if (isInteractionMenuShowing) {
    UserInterface::DrawMenu(player.inventory.weedInventoryVector,
                            "Click on seed to plant in pot");
  }
}
