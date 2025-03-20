#include <iostream>
#include <chrono>

#include "raylib.h"
#include "resource_dir.h"
#include "player.h"
#include "gameManager.h"


int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "myGame");

	SearchAndSetResourceDir("resources");

	Player player;
	
	Player* playerPtr = &player;
	std::shared_ptr<Computer> pc = std::make_shared<Computer>();

	
  const int fps = 60;

	SetTargetFPS(fps);

	Texture floor = LoadTexture("floor.png");

	std::vector<std::shared_ptr<Entity>> EntitiesDrawnToWorld;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		DrawTextureEx(floor, {0,0}, 0, 1.25f, WHITE);
		DrawTextureEx(player.getTexture(), player.getPosition(), 0, 1, WHITE);
		DrawTextureEx(pc->getTexture(), pc->getPosition(), 0, 1, WHITE);
		gameManager::rectCollision(pc, playerPtr);
		gameManager::objectVicinity(pc, playerPtr);
		playerPtr->move();
		playerPtr->buyWeed();
		playerPtr->inventory.dragItem(EntitiesDrawnToWorld);
		playerPtr->inventory.drawInventoryMenu();
		playerPtr->inventory.scrollInventoryMenu();
		

		for (auto& entity : EntitiesDrawnToWorld)
		{
			DrawTextureEx(entity->getTexture(), entity->getPosition(), 0, 1, WHITE);
			gameManager::objectVicinity(entity, playerPtr);
			gameManager::rectCollision(entity, playerPtr);
		}

		EndDrawing();
	}


	UnloadTexture(player.getTexture());
	for (int ent = 0; ent < EntitiesDrawnToWorld.size(); ent++)
		UnloadTexture(EntitiesDrawnToWorld[ent]->getTexture());


	CloseWindow();
	return 0;
	

}
