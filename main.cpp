#include "entity.h"
#include "gameManager.h"
#include "interactable.h"
#include "pch.h"
#include "player.h"
#include "resource_dir.h"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(800, 600, "myGame");

  SearchAndSetResourceDir("resources");

  std::unique_ptr<Player> player = std::make_unique<Player>();

  std::shared_ptr<Computer> pc = std::make_shared<Computer>();
  std::vector<std::shared_ptr<Interactable>> EntitiesDrawnToWorld;
  std::vector<std::shared_ptr<Entity>> ganjVec;

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
      if (gameManager::objectVicinity(entity, player)) {
        player->inventory.drawWeedSelection();
        entity->showInteractionUI(entity->getPositionX(),
                                  entity->getPositionY());
        entity->handleInteraction(*player, ganjVec);
      }
    }
    for (auto &entity : EntitiesDrawnToWorld) {
      gameManager::rectCollision(entity, player);
    }
    for (auto &ganja : ganjVec) {
      DrawTextureEx(ganja->getTexture(), ganja->getPosition(), 0, 1, WHITE);
    }

    EndDrawing();
  }

  UnloadTexture(player->getTexture());
  for (int ent = 0; ent < EntitiesDrawnToWorld.size(); ent++)
    UnloadTexture(EntitiesDrawnToWorld[ent]->getTexture());

  CloseWindow();
  return 0;
}
