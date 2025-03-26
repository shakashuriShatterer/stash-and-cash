#include "entity.h"
#include "interactable.h"

class PlantPot : public virtual Entity, public Interactable {
private:
  bool hasBeenPlanted;

public:
  PlantPot();
};
