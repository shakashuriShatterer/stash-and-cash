// clang-format off
#include "inventory.h"
#include "pch.h"
#include "store.h"
#include "interactable.h"
#include "pc.h"
#include "plantPot.h"
#include "userInterface.h"
#include <memory>
#include <raylib.h>
// clang-format on
//

Inventory Store::inventory;

bool Store::IsStoreShowing = false;

void Store::initialiseItems() {
  inventory.itemInventoryVector.clear();
  auto pc = std::make_shared<Computer>();
  std::shared_ptr<PlantPot> plantPot = std::make_shared<PlantPot>();

  // pc->setTexture(LoadTexture("pc.png"));
  // plantPot->setTexture(LoadTexture("plant_pot.png"));

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
  UserInterface::DrawMenu(inventory.itemInventoryVector,
                          "Click on an item to buy");
}

void Store::buyItem(Player &player) {
  auto item = inventory.GetSelectedItem();
  if (item) {
    player.inventory.itemInventoryVector.push_back(item);
    resetItems();
  }
}
