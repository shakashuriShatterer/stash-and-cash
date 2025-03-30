// clang-format off
#include "pch.h"
#include "pc.h"
#include "store.h"
// clang-format on

void Computer::setDesktopTexture(const Texture &newDesktopTexure) {
  desktopTexture = newDesktopTexure;
}

const Texture &Computer::getDesktopTexture() const { return desktopTexture; }

Computer::Computer() : Entity("pc") {
  setTexture(LoadTexture("pc.png"));
  setPosition({10, 10});
  desktopTexture = LoadTexture("desktop.jpg");
  setIsBeingDragged(false);
  setIsDraggable(false);
}

void Computer::drawInteractionMenu(Player &player) {
  if (isInteractionMenuShowing)
    Store::drawStore();
}
void Computer::handleInteraction(Player &player) { Store::buyItem(player); }
