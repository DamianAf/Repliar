#include "Repliar/repliar.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *shader = "#version 460 core\n"
                     "layout (location = 0) in vec3 aPos;\n"
                     "void main()\n"
                     "{\n"
                     "   gl_Position = vec4(aPos, 1.0);\n"
                     "}\0";
const char *shader2 = "#version 460 core\n"
                      "out vec4 FragColor;\n"
                      "void main()\n"
                      "{\n"
                      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange triangle\n"
                      "}\0";
unsigned int shaderSrc, shaderSrc2;
unsigned int program;

// functions
Repliar::Repliar(int width, int height, const char *title) : m_window(width, height, title) {

    glfwMakeContextCurrent(m_window.GetHandle());
    gladLoadGL();
    glViewport(0, 0, width, height);

    shaderSrc = glCreateShader(GL_VERTEX_SHADER);
    shaderSrc2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderSrc, 1, &shader, NULL);
    glShaderSource(shaderSrc2, 1, &shader2, NULL);
    glCompileShader(shaderSrc);
    glCompileShader(shaderSrc2);
    program = glCreateProgram();
    glAttachShader(program, shaderSrc);
    glAttachShader(program, shaderSrc2);
    glLinkProgram(program);
    glUseProgram(program);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
void Repliar::Render() {
    PrepareRender();
    glUseProgram(program);
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