#pragma once
#include "Repliar/window.hpp"
#include "Repliar/vector.hpp"
#include "Repliar/shader.hpp"

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
    Shader shader;

  private:
    void PrepareRender();
    void Render();
};
