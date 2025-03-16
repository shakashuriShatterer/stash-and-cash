#include "gameManager.h"
#include "player.h"

void gameManager::rectCollision(std::shared_ptr<Entity> object, Player* player)
{
    // Check for collision 
    if (object->getPositionX() < player->getPositionX() + player->getTextureWidth() &&
        object->getPositionX() + object->getTextureWidth() > player->getPositionX() &&
        object->getPositionY() < player->getPositionY() + player->getTextureHeight() &&
        object->getPositionY() + object->getTextureHeight() > player->getPositionY())
    {
        // Collision Resolution
        if (player->getPositionX() < object->getPositionX())
            player->setPositionX(player->getPositionX() - player->getMovementSpeed()); // Move player left
        if (player->getPositionX() > object->getPositionX())
            player->setPositionX(player->getPositionX() + player->getMovementSpeed()); // Move player right
        if (player->getPositionY() > object->getPositionY())
            player->setPositionY(player->getPositionY() + player->getMovementSpeed()); // Move player down
        if (player->getPositionY() < object->getPositionY())
            player->setPositionY(player->getPositionY() - player->getMovementSpeed()); // Move player up

        player->setCanMove(false); 
    }
    else
    {
        player->setCanMove(true); 
    }
}

// Similar to collision but with a bigger bounding box
void gameManager::objectVicinity(std::shared_ptr<Entity> object, Entity* player)
{
    const int vicinityRange = 50;
    // Check for vicinity 
    if (object->getPositionX() < player->getPositionX() + (player->getTextureWidth() + vicinityRange) &&
        object->getPositionX() + (object->getTextureWidth() + vicinityRange) > player->getPositionX() &&
        object->getPositionY() < player->getPositionY() + (player->getTextureHeight() + vicinityRange) &&
        object->getPositionY() + (object->getTextureHeight() + vicinityRange) > player->getPositionY())
    {
        // Draw letter E above player
        DrawRectangle((player->getPositionX() - 15), (player->getPositionY() - 15), 20, 20, BLACK);
        DrawText("E", (player->getPositionX() - 10), (player->getPositionY() - 10), 10, WHITE);

        if (IsKeyPressed(KEY_E))
            object->interactionMenu();
    }
}