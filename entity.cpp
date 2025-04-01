// clang-format off
#include "pch.h"
#include "entity.h"
 //clang-format on

int IdManager::nextId = 1;

int IdManager::idGenerator() { return nextId++; }

Entity::Entity(const std::string &entityName)
    : name(entityName), id(IdManager::idGenerator()) {
  texture = {1, 1, 1, 1};
  position = {0, 0};
  inventoryPosition = {10, 10};
  isBeingDragged = false;
  isDraggable = false;
  isInteractionMenuShowing = false;
}
void Entity::update() {};

// Setter definitions
void Entity::setTexture(const Texture &newTexture) {
  if (texture.id == 0) {
    std::cerr << "Invalid texture set to: " << name << std::endl;
  } else
    texture = newTexture;
}

void Entity::setTextureSize(const int newWidth, const int newHeight) {
  texture.width = newWidth;
  texture.height = newHeight;
}

void Entity::setPosition(const Vector2 &newPosition) {
  if (newPosition.x < 0 || newPosition.y < 0 ||
      newPosition.x + texture.width >= GetScreenWidth() ||
      newPosition.y + texture.height >= GetScreenHeight()) {
    std::cerr << "Position cannot be out of bounds: " << name << std::endl;

  } else
    position = newPosition;
}

void Entity::setPositionX(const float newPosX) {
  if (newPosX <= 0 || newPosX + texture.width >= GetScreenWidth()) {
    std::cerr << "X position cannot be out of bounds: " << name << std::endl;
  } else
    position.x = newPosX;
}

void Entity::setPositionY(const float newPosY) {
  if (newPosY <= 0 || newPosY + texture.height >= GetScreenHeight()) {
    std::cerr << "Y position cannot be out of bounds: " << name << std::endl;
  } else
    position.y = newPosY;
}

void Entity::setInventoryPosition(const Vector2 &newInventoryPosition) {
  inventoryPosition = newInventoryPosition;
}

void Entity::setInventoryPositionX(const float newPosX) {
  inventoryPosition.x = newPosX;
}

void Entity::setInventoryPositionY(const float newPosY) {
  inventoryPosition.y = newPosY;
}

void Entity::setIsBeingDragged(bool drag) {
  if (drag == true || drag == false)
    isBeingDragged = drag;
  else
    std::cerr << "invalid value set to isBeingDragged" << std::endl;
}

void Entity::setIsDraggable(bool drag) {
  if (drag == true || drag == false)
    isDraggable = drag;
  else
    std::cerr << "invalid value set to isDraggable" << std::endl;
}

void Entity::setIsInteractionMenuShowing(bool show) {
  isInteractionMenuShowing = show;
}

// Getter definitions
const Texture &Entity::getTexture() const { return texture; }
int Entity::getTextureWidth() const { return texture.width; }
int Entity::getTextureHeight() const { return texture.height; }
const Vector2 &Entity::getPosition() const { return position; }
float Entity::getPositionX() const { return position.x; }
float Entity::getPositionY() const { return position.y; }
const Vector2 &Entity::getInventoryPosition() const {
  return inventoryPosition;
}
float Entity::getInventoryPositionX() const { return inventoryPosition.x; }
float Entity::getInventoryPositionY() const { return inventoryPosition.y; }
int Entity::getId() const { return id; }
const std::string &Entity::getName() const { return name; }
bool Entity::getIsBeingDragged() const { return isBeingDragged; }
bool Entity::getIsDraggable() const { return isDraggable; }
bool Entity::getIsInteractionMenuShowing() const {
  return isInteractionMenuShowing;
}

void Entity::interactionMenu() {}


