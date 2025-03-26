#include "interactable.h"
#include "player.h"
#include <memory>
#include <vector>

void Interactable::showInteractionUI(float x, float y) {
  // Draw letter E above player
  DrawRectangle((x - 15), (y - 15), 20, 20, BLACK);
  DrawText("E", (x - 10), (y - 10), 10, WHITE);
}

void Interactable::handleInteraction(
    Player &player, std::vector<std::shared_ptr<Entity>> &entitesDrawnToWorld) {
  auto weed = player.inventory.GetSelectedWeed();
  if (weed) {
    weed->setPosition(getPosition());
    entitesDrawnToWorld.push_back(weed);
  }
}
