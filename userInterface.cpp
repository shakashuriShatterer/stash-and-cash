// clang-format off
#include "inventory.h"
#include "pch.h"
#include <memory>
#include <vector>
#include "userInterface.h"
// clang-format on
//

float UserInterface::scrollOffset = 5;

void UserInterface::DrawMenu(
    std::vector<std::shared_ptr<Interactable>> &inventory,
    std::string toolTip) {

  const float spacing = 70;
  const float startX = 10.f;
  float startY = 10.f;
  const int maxItemsPerRow = (GetRenderWidth() - startX) / spacing;

  DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(),
                Color{10, 10, 10, 218});
  const int toolTipSize = MeasureText(toolTip.c_str(), 20);
  const int toolTipPos = GetScreenWidth() / 2 - toolTipSize / 2;

  DrawText(toolTip.c_str(), toolTipPos, GetScreenHeight() - 50, 20, WHITE);

  int currentRow = 0;
  int currentColumn = 0;

  for (size_t i = 0; i < inventory.size(); i++) {
    float posX = startX + currentColumn * spacing;
    float posY = startY + scrollOffset + currentRow * spacing;

    auto &item = inventory[i];

    item->setInventoryPosition({posX, posY});

    DrawTextureEx(item->getTexture(), item->getInventoryPosition(), 0, 1,
                  WHITE);

    currentColumn++;

    if (currentColumn >= maxItemsPerRow) {
      currentColumn = 0;
      currentRow++;
    }
  }
}
