#include "Repliar/repliar.hpp"
#include "Repliar/shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// functions
Repliar::Repliar(int width, int height, const char* title) : m_window(width, height, title) {

    glfwMakeContextCurrent(m_window.GetHandle());
    gladLoadGL();
    glViewport(0, 0, width, height);

    shader.LoadShaders("./shaders/default.vert", "./shaders/default.frag");

    if (shader.id() == 0) {
        std::fprintf(stderr, "FATAL: Shader failed to load!\n");
        std::exit(1);
    }

    PrepareRender();

    running = true;
}
Repliar::~Repliar() {
}

void Repliar::PrepareRender() {
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
void Repliar::Render() {
    glUseProgram(shader.id());
    glClearColor(1.0f, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(m_window.GetHandle());
}

void Repliar::Update() {
    glfwMakeContextCurrent(m_window.GetHandle());
    if (running) {
        Render();
        glfwPollEvents();
        running = !glfwWindowShouldClose(m_window.GetHandle());
    }
}
