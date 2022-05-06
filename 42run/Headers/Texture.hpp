//
// Created by Diordychuk Dmitry on 28.04.2022.
//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad/glad.h"
#include "stb_image.h"

#include <string>

#include "GlError.hpp"


namespace ft {
    class Texture {
    private:
        unsigned int m_textureId;
        unsigned char *m_imageBuffer;

        int m_width, m_height, m_bitsPerPixel;

    public:
        Texture();
        ~Texture();

        void load(const std::string& filepath);
        void bind(unsigned int slot);
        void unbind();
    };

    struct ModelTexture {
        GLuint      id;
        std::string type;
    };
}

#endif //TEXTURE_HPP
