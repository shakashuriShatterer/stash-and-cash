#pragma once

#include <memory>
#include <vector>

#include "entity.h"
#include "player.h"

struct gameManager {
  gameManager();
  static void rectCollision(std::shared_ptr<Entity>, std::unique_ptr<Player> &);
  static void objectVicinity(std::shared_ptr<Entity>,
                             std::unique_ptr<Player> &);
};
