#pragma once

#include "Repliar/vector.hpp"
#include <STB/stb_image.h>
#include <glad/glad.h>
#include <iostream>

// TODO: implement the Collider component

enum ComponentType {
    NONE = 0,
    TRANSFORM_COMPONENT = (1U << 0),
    SPRITE_COMPONENT = (1U << 1),
    COLLIDER_COMPONENT = (1U << 2),
    CUSTOM_COMPONENT = (1U << 3),
};

namespace Component {
struct Transform {
    Vector2<float> position;
    struct scale {
        float x{1.0f};
        float y{1.0f};
    };
    struct rotation {
        float x;
        float y;
        float z;
    };
};

struct Sprite {
    void loadTexture(const std::string& path, bool flipVertically = true, bool srgb = false,
                     bool generateMipmaps = true) {
        stbi_set_flip_vertically_on_load(flipVertically);

        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            std::cerr << "ERROR::LOADTEXTURE::Failed to load image: " << path << std::endl;
            return;
        }

        // Determine format
        GLenum internalFormat, format;
        if (channels == 4) {
            internalFormat = srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8;
            format = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = srgb ? GL_SRGB8 : GL_RGB8;
            format = GL_RGB;
        } else if (channels == 1) {
            internalFormat = GL_R8;
            format = GL_RED;
        } else {
            std::cerr << "ERROR::LOADTEXTURE::Unsupported channel count: " << channels << " in " << path << std::endl;
            stbi_image_free(data);
            return;
        }

        // Generate and bind texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Upload data
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, generateMipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (width > 1 || height > 1) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // Clean up
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_textureID = textureID;
    }

    GLuint getTexture() {
        return m_textureID;
    }

  private:
    GLuint m_textureID;
};

struct Collider {};
struct Custom {
    virtual ~Custom() = default;
};
} // namespace Component
