// clang-format off
#include "pch.h"
#include "interactable.h"
#include "player.h"
#include <memory>
#include <vector>
// clang-format on

void Interactable::showInteractionUI(float x, float y) {
  // Draw letter E above player
  DrawRectangle((x - 15), (y - 15), 20, 20, BLACK);
  DrawText("E", (x - 10), (y - 10), 10, WHITE);
}

void Interactable::drawInteractionMenu(Player &) {
  std::cerr << "fdsk,jfhsuk,f\n";
}

void Interactable::handleInteraction(
    Player &player, std::vector<std::shared_ptr<Entity>> &entitesDrawnToWorld) {
  std::cerr << "Default handleInteraction\n";
}
void Interactable::handleInteraction(Player &player) {}
