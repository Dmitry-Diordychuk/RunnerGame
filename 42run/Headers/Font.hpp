//
// Created by ebona on 15.06.2022.
//

#ifndef INC_42RUN_FONT_HPP
#define INC_42RUN_FONT_HPP

#include "Pointer.hpp"
#include "Texture.hpp"
#include "Model.hpp"

namespace ft {
    class Font {
    public:
        Font(const string& path, int cellHeight, int cellWidth);
        Font(const Font& font);
        Font& operator=(const Font& font) = default;
        ~Font() = default;

        int width() const { return m_cellWidth; }
        int height() const { return m_cellHeight; }

        int offset(int ch) const;
        int line(int ch) const;

        Ref<Texture> texture() { return m_texture; }

    private:
        Ref<Texture> m_texture;
        int m_cellHeight;
        int m_cellWidth;
        int m_textureHeight;
        int m_textureWidth;

    };
}

#endif //INC_42RUN_FONT_HPP
