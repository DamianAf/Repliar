#pragma once
#include <functional>
#include "Repliar/vector.h"
// TODO: implement collider stuff

class Entity {
  public:
    Vector2<float> position;
    int width, height;
    bool isVisible;
    bool isColliding;

  public:
    Entity();
    void SetTexture();
    std::function<void(float dt)> Start;
    std::function<void(float dt)> Update;

  private:
};
