#include "Repliar/repliar.hpp"
#include "Repliar/ECS/components.hpp"
#include "Repliar/ECS/entityManager.hpp"
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
    // Square as two triangles
    // clang-format off
    float vertices[] = {
        -0.5f, -0.5f,    0.0f, 0.0f,
             0.5f, -0.5f,    1.0f, 0.0f,
             0.5f,  0.5f,    1.0f, 1.0f,
            -0.5f, -0.5f,    0.0f, 0.0f,
             0.5f,  0.5f,    1.0f, 1.0f,
            -0.5f,  0.5f,    0.0f, 1.0f
    };
    // clang-format on
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    constexpr GLuint stride = 4 * sizeof(float);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

// TODO: abstract the code so it works for all entities
void Repliar::Render() {
    glUseProgram(shader.id());
    glClearColor(1.0f, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    auto& spriteComp =
            EntityManager::getComponent<Component::Sprite>(0); // using 0 to get the first entity as a placeholder
    glBindTexture(GL_TEXTURE_2D, spriteComp.getTexture());
    shader.SetInt("inTexture", 0);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(m_window.GetHandle());
}

void Repliar::Start() {
    EntityManager::RunOnStartFunctions();
}

void Repliar::Update() {
    glfwMakeContextCurrent(m_window.GetHandle());
    if (running) {
        Render();
        glfwPollEvents();
        running = !glfwWindowShouldClose(m_window.GetHandle());
    }
}
