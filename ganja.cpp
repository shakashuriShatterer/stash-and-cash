// clang-format off
#include "pch.h"
#include "ganja.h"
// clang-format on

const std::chrono::steady_clock::time_point Ganja::getTimePlanted() const {
  return timePlanted;
}
const std::chrono::steady_clock::time_point Ganja::getTimePlantedNew() const {
  return timePlantedNew;
}
const std::chrono::duration<double> Ganja::getTimeElapsed() const {
  return timePlantedElapsed;
}

Ganja::Ganja() : Entity("weed") {
  setTexture(LoadTexture("ganja.png"));
  setInventoryPosition({10, 10});
  setTextureSize(50, 50);
  growthCount = 0;
  timePlanted = std::chrono::steady_clock::now();
}

void Ganja::interactionMenu() {
  if (getIsInteractionMenuShowing())
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(),
                  Color{10, 10, 10, 218});
}

void Ganja::grow() {
  timePlantedNew = std::chrono::steady_clock::now();
  timePlantedElapsed =
      std::chrono::duration_cast<std::chrono::duration<double>>(timePlantedNew -
                                                                timePlanted);

  if (timePlantedElapsed.count() > 5) {
    timePlanted = std::chrono::steady_clock::now();
    setTextureSize(getTextureWidth() + 20, getTextureHeight() + 20);
    setPosition({getPositionX() - 20, getPositionY() - 40});
  }
}
