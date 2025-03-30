#pragma once

#include "entity.h"
#include "pch.h"
#include "player.h"

struct gameManager {
  gameManager();
  // static const int
  static void rectCollision(std::shared_ptr<Entity>, std::unique_ptr<Player> &);
  static bool objectVicinity(std::shared_ptr<Entity>,
                             std::unique_ptr<Player> &);
};
