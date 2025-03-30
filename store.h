#include "inventory.h"
#include "player.h"

class Store {
public:
  static bool IsStoreShowing;
  static Inventory inventory;
  static void initialiseItems();
  static void resetItems();
  static void drawStore();
  static void buyItem(Player &);
};
