#pragma once

#include <glad/glad.h>
#include <string>

// Maybe: add comments to public functions

class Shader {
  public:
    explicit Shader(const char* vertexPath, const char* fragmentPath);
    explicit Shader();
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void SetInt(const char* name, int value) const;
    void SetFloat(const char* name, float value) const;
    void SetVec2(const char* name, float x, float y) const;
    void SetVec3(const char* name, float x, float y, float z) const;
    void SetMat4(const char* name, const float* matrix) const; // TODO: switch to using glm matrices

    [[nodiscard]] GLuint id() const {
        return m_program;
    }

    void LoadShaders(const char* vertexPath, const char* fragmentPath);

  private:
    GLuint m_program;

  private:
    GLuint CompileShader(GLenum type, const char* source) const;
    std::string ReadFile(const char* path) const;
};
