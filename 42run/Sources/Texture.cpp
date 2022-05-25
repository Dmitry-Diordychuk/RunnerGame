//
// Created by ebona on 04.05.2022.
//

#include "Texture.hpp"

ft::Texture::Texture()
    : m_imageBuffer(nullptr), m_width(0), m_height(0), m_bitsPerPixel(0)
{
    GLCall(glGenTextures(1, &m_textureId));
}

ft::Texture::Texture(const string &filepath) : m_imageBuffer(nullptr), m_width(0), m_height(0), m_bitsPerPixel(0) {
    GLCall(glGenTextures(1, &m_textureId));
    load(filepath);
}

ft::Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_textureId));
}

void ft::Texture::load(const string &filepath) {
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    stbi_set_flip_vertically_on_load(1);

    string path = PROJECT_SOURCE_DIR;
    m_imageBuffer = stbi_load((path + filepath).c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);
    if (m_imageBuffer)
    {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageBuffer));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        ASSERT(false);
    }
    stbi_image_free(m_imageBuffer);
}


void ft::Texture::bind(unsigned int slot) {
    ASSERT(slot < 8);

    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
}

void ft::Texture::unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
