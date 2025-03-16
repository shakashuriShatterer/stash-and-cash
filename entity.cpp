#include <iostream>


#include "entity.h"
#include "entity.h"

int IdManager::nextId = 1;

int IdManager::idGenerator()
{
    return nextId++;
}

Entity::Entity(const std::string& entityName)
    : name(entityName), id(IdManager::idGenerator())
{
    texture = {1,1,1,1};
    position = { 0,0 };
    inventoryPosition = { 10,10 };
    isBeingDragged = false;
    isDraggable = false;

}
void Entity::update() {};


// Setter definitions
void Entity::setTexture(const Texture& newTexture)
{
    if (texture.id == 0)
    {
        std::cerr << "Invalid texture set to: " << name << std::endl;
    }
    else
        texture = newTexture;
}

void Entity::setTextureSize(const int newWidth, const int newHeight )
{
    texture.width = newWidth;
    texture.height = newHeight;
}

void Entity::setPosition(const Vector2& newPosition)
{
    if (newPosition.x < 0 || newPosition.y < 0  || newPosition.x + texture.width >= GetScreenWidth() || newPosition.y + texture.height >= GetScreenHeight() )
    {
        std::cerr << "Position cannot be out of bounds: " << name << std::endl;

    }
    else
        position = newPosition;
}

void Entity::setPositionX(const float newPosX)
{
    if (newPosX <= 0 || newPosX + texture.width >=  GetScreenWidth())
    {
        std::cerr << "X position cannot be out of bounds: " << name << std::endl;
    }
    else
        position.x = newPosX;
}

void Entity::setPositionY(const float newPosY)
{
    if (newPosY <= 0  || newPosY + texture.height >= GetScreenHeight())
    {
        std::cerr << "Y position cannot be out of bounds: " << name << std::endl;
    }
    else
        position.y = newPosY;
}

void Entity::setInventoryPosition(const Vector2& newInventoryPosition)
{
    inventoryPosition = newInventoryPosition;
}

void Entity::setInventoryPositionX(const float newPosX)
{
    inventoryPosition.x = newPosX;
}

void Entity::setInventoryPositionY(const float newPosY)
{
    inventoryPosition.y = newPosY;
}

void Entity::setIsBeingDragged(bool drag)
{
    if (drag == true || drag == false)
        isBeingDragged = drag;
    else
        std::cerr << "invalid value set to isBeingDragged" << std::endl;

}

void Entity::setIsDraggable(bool drag)
{
    if (drag == true || drag == false)
        isDraggable = drag;
    else
        std::cerr << "invalid value set to isDraggable" << std::endl;

}
// Getter definitions
const Texture& Entity::getTexture() const{ return texture; }
int Entity::getTextureWidth() const{ return texture.width; }
int Entity::getTextureHeight() const{ return texture.height; }
const Vector2& Entity::getPosition() const{ return position; }
float Entity::getPositionX() const { return position.x;  }
float Entity::getPositionY() const { return position.y;  }
const Vector2& Entity::getInventoryPosition() const{ return inventoryPosition; }
float Entity::getInventoryPositionX() const{ return inventoryPosition.x; }
float Entity::getInventoryPositionY() const{ return inventoryPosition.y; }
int Entity::getId() const { return id; }
const std::string& Entity::getName() const { return name; }
bool Entity::getIsBeingDragged() const { return isBeingDragged; }
bool Entity::getIsDraggable() const { return isDraggable; }


void Entity::interactionMenu()
{
}

void Computer::setDesktopTexture(const Texture& newDesktopTexure)
{
    desktopTexture = newDesktopTexure;
}

const Texture& Computer::getDesktopTexture() const { return desktopTexture; }

Computer::Computer()
    :Entity("pc")
{
    setTexture(LoadTexture("pc.png"));
    setPosition({ 10,10 });
    desktopTexture = LoadTexture("desktop.jpg");
    setIsBeingDragged(false);
    setIsDraggable(false);
}


void Computer::interactionMenu()
{
    DrawTextureEx(desktopTexture, { 0, 0 }, 0, 1.25f, WHITE);
}

const std::chrono::steady_clock::time_point Ganja::getTimePlanted() const { return timePlanted; }
const std::chrono::steady_clock::time_point Ganja::getTimePlantedNew() const { return timePlantedNew; }
const std::chrono::duration<double> Ganja::getTimeElapsed() const { return timePlantedElapsed; }

Ganja::Ganja()
    :Entity("weed")
{
    setTexture(LoadTexture("ganja.png"));
    setInventoryPosition({ 10,10 });
    setTextureSize(50, 50);
    growthCount = 0;
    timePlanted = std::chrono::steady_clock::now();
    setIsBeingDragged(false);
    setIsDraggable(false);
}

void Ganja::interactionMenu()
{
}

void Ganja::grow() 
{
    timePlantedNew = std::chrono::steady_clock::now();
    timePlantedElapsed = std::chrono::duration_cast<std::chrono::duration<double>>(timePlantedNew - timePlanted);

    if (timePlantedElapsed.count() > 5)
    {
        timePlanted = std::chrono::steady_clock::now();
        setTextureSize(getTextureWidth() + 20, getTextureHeight() + 20);
        setPosition({ getPositionX() - 20, getPositionY() - 40 });
    }
}