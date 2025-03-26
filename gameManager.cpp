
#include "gameManager.h"
#include "pch.h"
#include "player.h"

void gameManager::rectCollision(std::shared_ptr<Entity> object,
                                std::unique_ptr<Player> &player) {
  // Check for collision
  if (object->getPositionX() <
          player->getPositionX() + player->getTextureWidth() &&
      object->getPositionX() + object->getTextureWidth() >
          player->getPositionX() &&
      object->getPositionY() <
          player->getPositionY() + player->getTextureHeight() &&
      object->getPositionY() + object->getTextureHeight() >
          player->getPositionY()) {
    // Collision Resolution
    if (player->getPositionX() < object->getPositionX())
      player->setPositionX(player->getPositionX() -
                           player->getMovementSpeed()); // Move player left
    if (player->getPositionX() > object->getPositionX())
      player->setPositionX(player->getPositionX() +
                           player->getMovementSpeed()); // Move player right
    if (player->getPositionY() > object->getPositionY())
      player->setPositionY(player->getPositionY() +
                           player->getMovementSpeed()); // Move player down
    if (player->getPositionY() < object->getPositionY())
      player->setPositionY(player->getPositionY() -
                           player->getMovementSpeed()); // Move player up

    player->setCanMove(false);
  } else {
    player->setCanMove(true);
  }
}

// Similar to collision but with a bigger bounding box
bool gameManager::objectVicinity(std::shared_ptr<Entity> object,
                                 std::unique_ptr<Player> &player) {
  const int vicinityRange = 50;
  // Check for vicinity
  if (object->getPositionX() <
          player->getPositionX() +
              (player->getTextureWidth() + vicinityRange) &&
      object->getPositionX() + (object->getTextureWidth() + vicinityRange) >
          player->getPositionX() &&
      object->getPositionY() <
          player->getPositionY() +
              (player->getTextureHeight() + vicinityRange) &&
      object->getPositionY() + (object->getTextureHeight() + vicinityRange) >
          player->getPositionY()) {
    return true;

  } else
    return false;
}
