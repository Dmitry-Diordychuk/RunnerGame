//
// Created by ebona on 15.06.2022.
//
#include "Font.hpp"

namespace ft {
    Font::Font(const string &path, int cellHeight, int cellWidth) {
        m_texture = make_unique<Texture>(path);
        m_cellHeight = cellHeight;
        m_cellWidth = cellWidth;
        m_textureHeight = m_texture->height();
        m_textureWidth = m_texture->width();
    }

    Font::Font(const Font &font) {
        m_texture = font.m_texture;
        m_cellHeight = font.m_cellHeight;
        m_cellWidth = font.m_cellWidth;
        m_textureHeight = font.m_textureHeight;
        m_textureWidth = font.m_textureWidth;
    }

    int Font::offset(int ch) const {
        return ((ch - 32) * m_cellWidth % m_textureWidth);
    }

    int Font::line(int ch) const {
        return (((m_textureHeight / m_cellHeight) - (ch - 32) * m_cellWidth / m_textureWidth) - 1) * m_cellHeight;
    }
}
