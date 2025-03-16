#pragma once

#include <vector>

#include "player.h"
#include "entity.h"


struct gameManager
{
	Vector2 screenSize = { 800, 600 };
	//	std::vector<Entity>entityList{};
	static void rectCollision(std::shared_ptr<Entity>, Player*);
	static void objectVicinity(std::shared_ptr<Entity>, Entity*);
};