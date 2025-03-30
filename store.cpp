// clang-format off
#include "inventory.h"
#include "pch.h"
#include "store.h"
#include "interactable.h"
#include "pc.h"
#include "plantPot.h"
#include <memory>
#include <raylib.h>
// clang-format on
//

Inventory Store::inventory;

bool Store::IsStoreShowing = false;

void Store::initialiseItems() {
  inventory.itemInventoryVector.clear();
  auto pc = std::make_shared<Computer>();
  auto plantPot = std::make_shared<PlantPot>();

  pc->setTexture(LoadTexture("pc.png"));
  plantPot->setTexture(LoadTexture("plant_pot.png"));

  inventory.itemInventoryVector.push_back(pc);
  inventory.itemInventoryVector.push_back(plantPot);
}

void Store::resetItems() {
  for (int i = 0; i < inventory.itemInventoryVector.size(); i++) {
    UnloadTexture(inventory.itemInventoryVector[i]->getTexture());
  }
  initialiseItems();
}

void Store::drawStore() {
  const float spacing = 70.0f;
  const float startX = 100.f;
  float startY = 10.f;
  const int maxItemsPerRow = (GetRenderWidth() - startX) / spacing;
  const Vector2 position = {100, 100};

  int currentRow = 0;
  int currentColumn = 0;

  for (auto it = inventory.itemInventoryVector.begin();
       it < inventory.itemInventoryVector.end(); it++) {
    float posX = startX + currentColumn * spacing;
    float posY = startY + inventory.scrollOffset + currentRow * spacing;

    (*it)->setInventoryPosition({posX, posY});

    DrawTextureEx((*it)->getTexture(), (*it)->getInventoryPosition(), 0, 1,
                  WHITE);

    currentColumn++;

    if (currentColumn >= maxItemsPerRow) {
      currentColumn = 0;
      currentRow++;
    }
  }
  // for (int i = 0; i < inventory.itemInventoryVector.size(); i++) {
  // DrawTexture(inventory.itemInventoryVector[i]->getTexture(),
  // position.x + (i * spacing), position.y, WHITE);
  // }
}

void Store::buyItem(Player &player) {
  auto item = inventory.GetSelectedItem();
  if (item) {
    player.inventory.itemInventoryVector.push_back(item);
    resetItems();
  }
}
