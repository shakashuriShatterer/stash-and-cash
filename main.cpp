#include <memory>

#include "gameManager.h"
#include "player.h"
#include "raylib.h"
#include "resource_dir.h"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(800, 600, "myGame");

  SearchAndSetResourceDir("resources");

  std::unique_ptr<Player> player = std::make_unique<Player>();

  std::shared_ptr<Computer> pc = std::make_shared<Computer>();
  std::vector<std::shared_ptr<Entity>> EntitiesDrawnToWorld;

  const int fps = 60;

  SetTargetFPS(fps);

  Texture floor = LoadTexture("floor.png");

  while (!WindowShouldClose()) {
    BeginDrawing();

    DrawTextureEx(floor, {0, 0}, 0, 1.25f, WHITE);
    DrawTextureEx(player->getTexture(), player->getPosition(), 0, 1, WHITE);
    DrawTextureEx(pc->getTexture(), pc->getPosition(), 0, 1, WHITE);
    gameManager::rectCollision(pc, player);
    gameManager::objectVicinity(pc, player);
    player->move();
    player->buyWeed();
    player->inventory.dragItem(EntitiesDrawnToWorld);
    player->inventory.drawInventoryMenu();
    player->inventory.scrollInventoryMenu();

    for (auto &entity : EntitiesDrawnToWorld) {
      DrawTextureEx(entity->getTexture(), entity->getPosition(), 0, 1, WHITE);
      gameManager::objectVicinity(entity, player);
      gameManager::rectCollision(entity, player);
    }

    EndDrawing();
  }

  UnloadTexture(player->getTexture());
  for (int ent = 0; ent < EntitiesDrawnToWorld.size(); ent++)
    UnloadTexture(EntitiesDrawnToWorld[ent]->getTexture());

  CloseWindow();
  return 0;
}
