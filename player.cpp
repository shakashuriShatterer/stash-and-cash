// clang-format off
#include "pch.h"
#include "player.h"
#include "entity.h"
#include "plantPot.h"
// clang-format on
Player::Player() : Entity("player") {
  setTexture(LoadTexture("sprite-0001.png"));
  setTextureSize(100, 100);
  setPosition({100, 20});
  movementSpeed = 5;
  canMove = true;
}

void Player::setCanMove(bool move) { canMove = move; }

bool Player::getCanMove() const { return canMove; }
int Player::getMovementSpeed() const { return movementSpeed; }

void Player::move() {
  if (canMove && !inventory.isInventoryShowing) {
    Vector2 direction = {0, 0};
    if (IsKeyDown(KEY_W))
      direction.y -= 1;
    if (IsKeyDown(KEY_S))
      direction.y += 1;
    if (IsKeyDown(KEY_A))
      direction.x -= 1;
    if (IsKeyDown(KEY_D))
      direction.x += 1;

    // normalising vector to fix diagonal speed
    if (direction.x != 0 || direction.y != 0) {
      float magnitude =
          sqrt(direction.y * direction.y + direction.x * direction.x);

      direction.x /= magnitude;
      direction.y /= magnitude;
    }

    setPositionX({getPositionX() + direction.x * movementSpeed});
    setPositionY({getPositionY() + direction.y * movementSpeed});
  }
}

void Player::buyWeed() {
  static bool keyPessedOnce = false;

  if (IsKeyPressed(KEY_B) && !keyPessedOnce) {
    std::shared_ptr<PlantPot> newPot = std::make_shared<PlantPot>();
    std::shared_ptr<Ganja> newWeed = std::make_shared<Ganja>();
    inventory.itemInventoryVector.push_back(newPot);
    inventory.weedInventoryVector.push_back(newWeed);
    keyPessedOnce = true;
  }
  if (IsKeyReleased(KEY_B))
    keyPessedOnce = false;
}
