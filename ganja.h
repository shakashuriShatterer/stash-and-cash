#pragma once
#include "entity.h"
#include "interactable.h"

class Ganja : public virtual Entity, public Interactable {
private:
  std::chrono::steady_clock::time_point timePlanted, timePlantedNew;
  std::chrono::duration<double> timePlantedElapsed;
  int growthCount;

public:
  Ganja();
  void update() override { grow(); }
  void interactionMenu() override;
  void grow();
  // setters
  void setTimePlanted(const std::chrono::steady_clock &);
  void setTimeNew(const std::chrono::steady_clock &);

  // getters
  const std::chrono::steady_clock::time_point getTimePlanted() const;
  const std::chrono::steady_clock::time_point getTimePlantedNew() const;
  const std::chrono::duration<double> getTimeElapsed() const;
};
