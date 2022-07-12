//
// Created by ebona on 20.06.2022.
//

#include "Text.hpp"

namespace ft {
    Text::Text(const string& text, glm::vec3 pos, Font* font) {
        m_str = text;
        m_font = Ref<Font>(font);
        m_pos = pos;
        createGlyphs();
    }

    void Text::update(const string& text) {
        m_str = text;
        removeGlyphs();
        createGlyphs();
    }

    void Text::createGlyphs() {
        glm::vec3 pos = m_pos;
        for (auto &ch : m_str) {
            Ref<Model> model = make_shared<Model>();

            int offset = m_font->offset(ch);
            int line = m_font->line(ch);
            float xUV = (float)offset / (float)m_font->texture()->width();
            float yUV = (float)line / (float)m_font->texture()->height();
            float glyphWidth = (float)m_font->width() / (float)m_font->texture()->width();
            float glyphHeight = (float)m_font->height() / (float)m_font->texture()->height();

            model->loadGlyphQuad(
                    pos + glm::vec3(m_font->width(), 0.0f, 0.0f),
                    glm::vec2(m_font->width(), m_font->height()),
                    glm::vec2(glyphWidth, glyphHeight),
                    glm::vec2(xUV, yUV));
            m_glyphs.push_back(model);
            pos.x += (float)m_font->width();
        }
    }

    void Text::removeGlyphs() {
        m_glyphs.clear();
    }


}