#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <cassert>
#include <fstream>

// Standard Headers
#include <string>

#include "GlError.hpp"

#include "Pointer.hpp"

// Define Namespace
namespace ft {
    using namespace std;

    class Shader {
    private:
        // Private Member Variables
        GLuint m_Program;
        GLint m_Status{};
        GLint m_Length{};

        // Disable Copying and Assignment
        Shader(Shader const &) = delete;

        Shader &operator=(Shader const &) = delete;

    public:

        // Implement Custom Constructor and Destructor
        Shader() { m_Program = glCreateProgram(); }

        ~Shader() { glDeleteProgram(m_Program); }

        // Public Member Functions
        const Shader &activate() const;

        void deactivate() const;

        Shader &attach(string const &filename);

        GLuint create(string const &filename);

        GLuint get() const { return m_Program; }

        Shader &link();

        // Wrap Calls to glUniform
        void bind(unsigned int location, float value);
        void bind(unsigned int location, glm::vec3 const &vec);
        void bind(unsigned int location, glm::mat4 const &matrix);

        template<typename T>
        Shader &bind(string const &name, T &value) {
            int location = glGetUniformLocation(m_Program, name.c_str());
            if (location == -1) {
                cout << "Shader error: failed to bind " << name << " uniform" << endl;
                ASSERT(false);
            } else {
                bind(location, forward<T>(value));
            }
            return *this;
        }

        template<typename T>
        Shader &bind(string const &name, T &&value) {
            int location = glGetUniformLocation(m_Program, name.c_str());
            if (location == -1) {
                cout << "Shader error: failed to bind " << name << " uniform" << endl;
                ASSERT(false);
            } else {
                bind(location, forward<T>(value));
            }
            return *this;
        }
    };
};
