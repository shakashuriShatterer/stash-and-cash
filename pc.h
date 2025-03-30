#include "interactable.h"

class Computer : virtual public Entity, public Interactable {
private:
  Texture desktopTexture;

public:
  Computer();
  // setters
  void setDesktopTexture(const Texture &);
  // getters
  const Texture &getDesktopTexture() const;
  void drawInteractionMenu(Player &) override;
  void handleInteraction(Player &) override;
};
