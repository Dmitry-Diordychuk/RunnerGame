//
// Created by ebona on 20.06.2022.
//

#ifndef INC_42RUN_TEXT_HPP
#define INC_42RUN_TEXT_HPP

#include "GameObject.hpp"
#include "Font.hpp"

namespace ft {
    class Text {
    public:
        Text(const string& text, glm::vec3 pos, Font* font);

        vector<Ref<Model>>::iterator begin() { return m_glyphs.begin(); }
        vector<Ref<Model>>::iterator end() { return m_glyphs.end(); }

        Ref<Font> font() { return m_font; }

        void update(const string& text);

        void createGlyphs();
        void removeGlyphs();

        void position(glm::vec3 pos) { m_pos = pos; }

    private:
        Ref<Font> m_font;
        vector<Ref<Model>> m_glyphs;
        string m_str;
        glm::vec3 m_pos;

    };
}

#endif //INC_42RUN_TEXT_HPP
