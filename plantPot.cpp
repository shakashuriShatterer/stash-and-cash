// clang-format off
#include "pch.h"
#include "plantPot.h"
#include "entity.h"
#include "interactable.h"
#include "player.h"
#include <memory>
#include <vector>
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
    weed->setPosition(getPosition());
    entitiesDrawnToWorld.push_back(weed);
    std::cerr << "removing weedId: " << weed->getId() - 2;
    player.inventory.weedInventoryVector.erase(
        player.inventory.weedInventoryVector.begin() + (weed->getId() - 2));
  }
}

void PlantPot::drawInteractionMenu(Player &player) {

  if (isInteractionMenuShowing) {

    const float spacing = 50;
    const float startX = 10.f;
    float startY = 10.f;
    const int maxItemsPerRow = (GetRenderWidth() - startX) / spacing;

    // if (IsKeyPressed(KEY_E))
    // player.inventory.isWeedInventoryShowing = true;
    // if (IsKeyPressed(KEY_Q))
    // player.inventory.isWeedInventoryShowing = false;

    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(),
                  Color{10, 10, 10, 218});
    const std::string inventoryTip =
        "Click on a weed item to plant in pot. press 'Q' to close.";
    const int inventoryTipSize = MeasureText(inventoryTip.c_str(), 20);
    const int inventoryTipPos = GetScreenWidth() / 2 - inventoryTipSize / 2;

    DrawText(inventoryTip.c_str(), inventoryTipPos, GetScreenHeight() - 50, 20,
             WHITE);

    int currentRow = 0;
    int currentColumn = 0;

    for (size_t i = 0; i < player.inventory.weedInventoryVector.size(); i++) {
      float posX = startX + currentColumn * spacing;
      float posY =
          startY + player.inventory.scrollOffset + currentRow * spacing;

      auto &weed = player.inventory.weedInventoryVector[i];

      weed->setInventoryPosition({posX, posY});

      DrawTextureEx(weed->getTexture(), weed->getInventoryPosition(), 0, 1,
                    WHITE);

      currentColumn++;

      if (currentColumn >= maxItemsPerRow) {
        currentColumn = 0;
        currentRow++;
      }
    }
  }
}
