#pragma once

struct GLFWwindow;

class Window {
  public:
    int windowWidth;
    int windowHeight;

  public:
    Window(int width, int height, const char *title);
    void ChangeSize(int width, int height);
    void ChangeTitle(const char *title);
    GLFWwindow *GetHandle();

  private:
    GLFWwindow *m_window;
};