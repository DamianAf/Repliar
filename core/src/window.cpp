#include "Repliar/window.hpp"
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* title) : windowWidth(width), windowHeight(height) {
    glfwInit();
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
}

void Window::ChangeSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glfwSetWindowSize(m_window, width, height);
}
void Window::ChangeTitle(const char* title) {
    glfwSetWindowTitle(m_window, title);
}

GLFWwindow* Window::GetHandle() {
    return m_window;
}
