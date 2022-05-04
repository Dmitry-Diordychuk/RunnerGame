#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <string>

#include "GlError.hpp"

// Define Namespace
namespace ft
{
    class Shader
    {
    private:
        // Private Member Variables
        GLuint m_Program;
        GLint  m_Status{};
        GLint  m_Length{};

        // Disable Copying and Assignment
        Shader(Shader const &) = delete;
        Shader & operator=(Shader const &) = delete;

    public:

        // Implement Custom Constructor and Destructor
         Shader() { m_Program = glCreateProgram(); }
        ~Shader() { glDeleteProgram(m_Program); }

        // Public Member Functions
        const Shader & activate() const;
        void deactivate() const;
        Shader & attach(std::string const & filename);
        GLuint   create(std::string const & filename);
        GLuint   get() const { return m_Program; }
        Shader & link();

        // Wrap Calls to glUniform
        void bind(unsigned int location, float value);

        void bind(unsigned int location, glm::mat4 const & matrix);

        template<typename T>
        Shader & bind(std::string const & name, T&& value)
        {
            int location = glGetUniformLocation(m_Program, name.c_str());
            if (location == -1) {
                ASSERT(false);
            }
            else bind(location, std::forward<T>(value));
            return *this;
        }
    };
};
