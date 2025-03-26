#pragma once
#include "pch.h"

struct IdManager {
  static int nextId;
  static int idGenerator();
};

class Entity {
private:
  Texture texture;
  Vector2 position, inventoryPosition;
  const std::string name;
  const int id;
  bool isBeingDragged;
  bool isDraggable;
  bool isInteractionMenuShowing;

public:
  Entity(const std::string &);
  // Setters
  virtual void update();
  void setTexture(const Texture &);
  void setTextureSize(const int, const int);
  void setPosition(const Vector2 &);
  void setPositionX(const float);
  void setPositionY(const float);
  void setInventoryPosition(const Vector2 &);
  void setInventoryPositionX(const float);
  void setInventoryPositionY(const float);
  void setIsBeingDragged(bool);
  void setIsDraggable(bool);
  void setIsInteractionMenuShowing(bool);
  float scale = 1;

  // Getters
  const Texture &getTexture() const;
  int getTextureWidth() const;
  int getTextureHeight() const;
  const Vector2 &getPosition() const;
  float getPositionX() const;
  float getPositionY() const;
  const Vector2 &getInventoryPosition() const;
  float getInventoryPositionX() const;
  float getInventoryPositionY() const;
  int getId() const;
  const std::string &getName() const;
  bool getIsBeingDragged() const;
  bool getIsDraggable() const;
  bool getIsInteractionMenuShowing() const;

  virtual void interactionMenu();
};

class Computer : public Entity {
private:
  Texture desktopTexture;

public:
  Computer();
  void interactionMenu() override;
  // setters
  void setDesktopTexture(const Texture &);
  // getters
  const Texture &getDesktopTexture() const;
};

class Ganja : public Entity {
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
