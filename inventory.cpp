#include "inventory.h"
#include "interactable.h"
#include "pch.h"
#include "userInterface.h"

void Inventory::drawInventoryMenu() {
  if (isInventoryShowing) {
    for (auto item : itemInventoryVector)
      item->setIsDraggable(true);

    UserInterface::DrawMenu(itemInventoryVector, "Drag and drop item");
  } else
    for (auto item : itemInventoryVector)
      item->setIsDraggable(false);
}

void Inventory::scrollInventoryMenu() {
  const float scrollSpeed = 10.0f;

  // if (isInventoryShowing) {
  if (GetMouseWheelMove() < 0)
    UserInterface::scrollOffset -= scrollSpeed;
  if (GetMouseWheelMove() > 0)
    UserInterface::scrollOffset += scrollSpeed;
}
// }

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
  for (size_t i = 0; i < weedInventoryVector.size(); i++) {
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
  for (size_t i = 0; i < itemInventoryVector.size(); i++) {
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
