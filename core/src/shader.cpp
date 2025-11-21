#include "Repliar/shader.hpp"
#include <iostream>
#include <cstdio>
#include <string>

void Shader::LoadShaders(const char* vertexPath, const char* fragmentPath) {
    std::string vShaderCode = ReadFile(vertexPath);
    std::string fShaderCode = ReadFile(fragmentPath);
    if (vShaderCode.empty() || fShaderCode.empty())
        return;

    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vShaderCode.c_str());
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fShaderCode.c_str());
    if (!vertex || !fragment)
        return;

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        // Log error
        glDeleteProgram(m_program);
        m_program = 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_program(0) {
    LoadShaders(vertexPath, fragmentPath);
}

Shader::Shader() : m_program(0) {
}

Shader::~Shader() {
    if (m_program) {
        glDeleteProgram(m_program);
    }
}

std::string Shader::ReadFile(const char* path) const {
    FILE* file = std::fopen(path, "rb");
    if (!file)
        return {};

    std::fseek(file, 0, SEEK_END);
    long len = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);

    std::string buffer;
    buffer.resize(len);
    std::size_t bytesRead = std::fread(buffer.data(), 1, len, file);
    std::fclose(file);

    return buffer;
}

GLuint Shader::CompileShader(GLenum type, const char* source) const {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader Compilation Error: \n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
};

void Shader::Bind() const {
    glUseProgram(m_program);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetInt(const char* name, int value) const {
    GLint loc = glGetUniformLocation(m_program, name);
    if (loc != -1)
        glUniform1i(loc, value);
}

void Shader::SetFloat(const char* name, float value) const {
    GLint loc = glGetUniformLocation(m_program, name);
    if (loc != -1)
        glUniform1f(loc, value);
}

void Shader::SetVec2(const char* name, float x, float y) const {
    GLint loc = glGetUniformLocation(m_program, name);
    if (loc != -1)
        glUniform2f(loc, x, y);
}

void Shader::SetVec3(const char* name, float x, float y, float z) const {
    GLint loc = glGetUniformLocation(m_program, name);
    if (loc != -1)
        glUniform3f(loc, x, y, z);
}

void Shader::SetMat4(const char* name, const float* matrix) const {
    GLint loc = glGetUniformLocation(m_program, name);
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}
