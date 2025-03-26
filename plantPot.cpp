#include "plantPot.h"
#include "interactable.h"
PlantPot::PlantPot()
    : Entity("plantPot"), Interactable(), hasBeenPlanted(false) {
  hasBeenPlanted = false;
  setTexture(LoadTexture("plant_pot.png"));
  setInventoryPosition({20, 10});
  setTextureSize(50, 50);
}
