#pragma once
#include <vector>
#include "raylib.h"
#include "entity.h"

class Player : public Entity
{
private:
	bool canMove;
	int movementSpeed;
public:
	void move();
	void interact();
	void buyWeed();
	//setters
	void setCanMove(bool move);

	//getters
	bool getCanMove() const;
	int getMovementSpeed() const;

	Player();

	struct Inventory 
	{	
		bool isInventoryShowing = false;
		float scrollOffset = 5;
		std::vector<std::shared_ptr<Entity>> inventoryVector;
		void drawInventoryMenu();
		void scrollInventoryMenu();
		void dragItem(std::vector<std::shared_ptr<Entity>>&);
	
	};
	Inventory inventory;
};

