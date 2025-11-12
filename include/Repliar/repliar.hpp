#pragma once
#include "Repliar/window.hpp"
#include "Repliar/vector.hpp"

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
