#pragma once
#include "Repliar/window.h"
#include "Repliar/vector.h"

class Repliar {
  public:
    unsigned int VBO, VAO;
    bool running;

  public:
    Repliar(int width, int height, const char* title);
    ~Repliar();

    void Update();

  private:
    Window m_window;

  private:
    void PrepareRender();
    void Render();
};