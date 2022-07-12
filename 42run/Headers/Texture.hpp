//
// Created by Diordychuk Dmitry on 28.04.2022.
//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad/glad.h"
#include "GlError.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

namespace ft {
    using namespace std;

    class Texture {
    private:
        unsigned int m_textureId;
        unsigned char *m_imageBuffer;

        int m_width, m_height, m_bitsPerPixel;

    public:
        Texture();
        explicit Texture(const string& filepath);
        ~Texture();

        void load(const string& filepath);
        void bind(unsigned int slot);
        void unbind();

        int width() const { return m_width; }
        int height() const { return m_height; }
    };

    struct ModelTexture {
        GLuint      id;
        string type;
    };
}

#endif //TEXTURE_HPP
