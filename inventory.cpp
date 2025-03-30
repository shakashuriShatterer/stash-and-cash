#include "inventory.h"
#include "interactable.h"
#include "pch.h"

void Inventory::drawInventoryMenu() {
  const float spacing = 50;
  const float startX = 10.f;
  float startY = 10.f;
  const int maxItemsPerRow = (GetRenderWidth() - startX) / spacing;

  if (IsKeyPressed(KEY_TAB))
    isInventoryShowing = true;
  if (IsKeyPressed(KEY_Q))
    isInventoryShowing = false;

  if (isInventoryShowing) {
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(),
                  Color{10, 10, 10, 218});
    const std::string inventoryTip =
        "Drag and drop items to place in your room. press 'Q' to close.";
    const int inventoryTipSize = MeasureText(inventoryTip.c_str(), 20);
    const int inventoryTipPos = GetScreenWidth() / 2 - inventoryTipSize / 2;

    DrawText(inventoryTip.c_str(), inventoryTipPos, GetScreenHeight() - 50, 20,
             WHITE);

    int currentRow = 0;
    int currentColumn = 0;

    for (auto it = itemInventoryVector.begin(); it < itemInventoryVector.end();
         it++) {
      float posX = startX + currentColumn * spacing;
      float posY = startY + scrollOffset + currentRow * spacing;

      (*it)->setIsDraggable(true);
      (*it)->setInventoryPosition({posX, posY});

      DrawTextureEx((*it)->getTexture(), (*it)->getInventoryPosition(), 0, 1,
                    WHITE);

      currentColumn++;

      if (currentColumn >= maxItemsPerRow) {
        currentColumn = 0;
        currentRow++;
      }
    }
  } else {
    for (auto &item : itemInventoryVector)
      item->setIsDraggable(false);
  }
}

void Inventory::scrollInventoryMenu() {
  const float scrollSpeed = 10.0f;

  if (isInventoryShowing || isWeedInventoryShowing) {
    if (GetMouseWheelMove() < 0)
      scrollOffset -= scrollSpeed;
    if (GetMouseWheelMove() > 0)
      scrollOffset += scrollSpeed;
  }
}

void Inventory::dragItem(
    std::vector<std::shared_ptr<Interactable>> &EntitiesDrawnToWorld) {
  for (size_t i = 0; i < itemInventoryVector.size(); i++) {
    auto &item = itemInventoryVector[i];
    if (item->getIsBeingDragged()) {
      item->setPosition(GetMousePosition());
      DrawTextureEx(item->getTexture(), item->getPosition(), 0, 1, WHITE);
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        item->setIsBeingDragged(false);
        EntitiesDrawnToWorld.push_back(item);
        itemInventoryVector.erase(itemInventoryVector.begin() + i);
        i--;
      }
    }
    if (CheckCollisionPointRec(
            GetMousePosition(),
            {item->getInventoryPositionX(), item->getInventoryPositionY(),
             static_cast<float>(item->getTextureWidth()),
             static_cast<float>(item->getTextureHeight())}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && item->getIsDraggable()) {
      item->setIsBeingDragged(true);
      isInventoryShowing = false;
    }
  }
}

std::shared_ptr<Entity> Inventory::GetSelectedWeed() {
  for (int i = 0; i < weedInventoryVector.size(); i++) {
    auto &weed = weedInventoryVector[i];
    Rectangle boundingBox = {weed->getInventoryPositionX(),
                             (weed->getInventoryPositionY()),
                             static_cast<float>(weed->getTextureWidth()),
                             static_cast<float>(weed->getTextureHeight())};

    if (CheckCollisionPointRec(GetMousePosition(), boundingBox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      return weed;
    }
  }
  return nullptr;
}

std::shared_ptr<Interactable> Inventory::GetSelectedItem() {
  for (int i = 0; i < itemInventoryVector.size(); i++) {
    auto &item = itemInventoryVector[i];
    Rectangle boundingBox = {item->getInventoryPositionX(),
                             (item->getInventoryPositionY()),
                             static_cast<float>(item->getTextureWidth()),
                             static_cast<float>(item->getTextureHeight())};

    if (CheckCollisionPointRec(GetMousePosition(), boundingBox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      return item;
    }
  }
  return nullptr;
}
