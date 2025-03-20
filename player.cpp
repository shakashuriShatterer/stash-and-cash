#include <algorithm>
#include <iostream>
#include <math.h>
#include "player.h"
#include "gameManager.h"

// gayboy hahahah smelly shit 
Player::Player()
	:Entity("player")
{
	setTexture(LoadTexture("sprite-0001.png"));
	setTextureSize(100, 100);
	setPosition({ 100,20 });
	movementSpeed = 5;
	canMove = true;
}

void Player::setCanMove(bool move) { canMove = move; }

bool Player::getCanMove() const { return canMove; }
int Player::getMovementSpeed() const { return movementSpeed; }


void Player::move()
{	
	if (canMove && !inventory.isInventoryShowing)
	{
		Vector2 direction = { 0,0 };
		if (IsKeyDown(KEY_W))
			direction.y -= 1;
		if (IsKeyDown(KEY_S))
			direction.y += 1;
		if (IsKeyDown(KEY_A))
			direction.x -= 1;
		if (IsKeyDown(KEY_D))
			direction.x += 1;

		// normalising vector to fix diagonal speed
		if (direction.x != 0 || direction.y != 0)
		{
			float magnitude = sqrt(direction.y * direction.y + direction.x * direction.x);

			direction.x /= magnitude ;
			direction.y /= magnitude ;
		}

		setPositionX({ getPositionX() + direction.x * movementSpeed });
		setPositionY({ getPositionY() + direction.y * movementSpeed });

	}
}

void Player::interact()
{
		if (IsKeyPressed(KEY_E))
			DrawRectangle(0, 0, 100, 100, YELLOW);

}

void Player::buyWeed()
{
	static bool keyPessedOnce = false;

	if (IsKeyPressed(KEY_B) && !keyPessedOnce)
	{
		std::shared_ptr<Ganja> newWeed = std::make_shared<Ganja>();
		inventory.inventoryVector.push_back(newWeed);
		std::cout << "weedId: " << newWeed->getId() << "\n";
		keyPessedOnce = true;

	}
	if (IsKeyReleased(KEY_B))
		keyPessedOnce = false;
}


void Player::Inventory::drawInventoryMenu()
{
	const float spacing = 50; 
	const float startX = 10.f;
	float startY = 10.f; 
	const int maxItemsPerRow = (GetRenderWidth() - startX) / spacing; 

	if (IsKeyPressed(KEY_TAB))
		isInventoryShowing = true;
	if (IsKeyPressed(KEY_Q))
		isInventoryShowing = false;

	if (isInventoryShowing)
	{
		DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Color{ 10,10,10,218 });
		const std::string inventoryTip = "Drag and drop items to place in your room. press 'Q' to close.";
		const int inventoryTipSize = MeasureText(inventoryTip.c_str(), 20);
		const int inventoryTipPos = GetScreenWidth() / 2 - inventoryTipSize / 2;

		DrawText(inventoryTip.c_str(), inventoryTipPos, GetScreenHeight() - 50, 20, WHITE);

		int currentRow = 0;
		int currentColumn = 0;

		for (auto it = inventoryVector.begin(); it < inventoryVector.end(); it++)
		{
			float posX = startX  + currentColumn * spacing;
			float posY = startY + scrollOffset +  currentRow * spacing;

			(*it)->setIsDraggable(true);
			(*it)->setInventoryPosition({ posX, posY });

			DrawTextureEx((*it)->getTexture(), (*it)->getInventoryPosition(), 0, 1, WHITE);

			currentColumn++;

			if (currentColumn >= maxItemsPerRow)
			{
				currentColumn = 0;
				currentRow++;    
			}
		}
	}
	else
	{
		for (auto& item : inventoryVector)
			item->setIsDraggable(false);
	}
}

void Player::Inventory::scrollInventoryMenu()
{
	const float scrollSpeed = 10.0f;

	if (isInventoryShowing)
	{
		if (GetMouseWheelMove() < 0)
			scrollOffset -= scrollSpeed;
		if (GetMouseWheelMove() > 0)
			scrollOffset += scrollSpeed;
	}
}

void Player::Inventory::dragItem(std::vector<std::shared_ptr<Entity>>& EntitiesDrawnToWorld)
{
	for (size_t i = 0; i < inventoryVector.size(); i++)
	{
		auto& item = inventoryVector[i];
		if (item->getIsBeingDragged())
		{
			item->setPosition(GetMousePosition());
			DrawTextureEx(item->getTexture(), item->getPosition(), 0, 1, WHITE);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				item->setIsBeingDragged(false);
				EntitiesDrawnToWorld.push_back(item);
				inventoryVector.erase(inventoryVector.begin() + i);
				i--;
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), {item->getInventoryPositionX(),item->getInventoryPositionY(), static_cast<float>(item->getTextureWidth()), static_cast<float>(item->getTextureHeight())}) 
			&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && item->getIsDraggable()) 
		{
			item->setIsBeingDragged(true);
			isInventoryShowing = false;
		}
	}
}


