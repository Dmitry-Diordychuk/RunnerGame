// Local Headers
#include "Shader.hpp"

// Define Namespace
namespace ft
{
    const Shader & Shader::activate() const
    {
        GLCall(glUseProgram(m_Program));
        return *this;
    }

    void Shader::deactivate() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::bind(unsigned int location, float value) { GLCall(glUniform1f(location, value)); }
    void Shader::bind(unsigned int location, glm::vec3 const &vec) { GLCall(glUniform3fv(location, 1, glm::value_ptr(vec))); }
    void Shader::bind(unsigned int location, glm::mat4 const & matrix)
    {
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    Shader & Shader::attach(string const & filename)
    {
        ASSERT(!filename.empty())

        // Load GLSL Shader Source from File
        string path = PROJECT_SOURCE_DIR;
        ifstream fd(path + filename);
        auto src = string(istreambuf_iterator<char>(fd),
                              (istreambuf_iterator<char>()));

        // create a Shader Object
        const char * source = src.c_str();
        auto shader = create(filename);
        GLCall(glShaderSource(shader, 1, & source, nullptr));
        GLCall(glCompileShader(shader));
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, & m_Status));

        // Display the Build Log on Error
        if (m_Status == false)
        {
            GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, & m_Length));
            Scope<char[]> buffer(new char[m_Length]);
            GLCall(glGetShaderInfoLog(shader, m_Length, nullptr, buffer.get()));
            cout << "Shader error: " << buffer.get() << endl;
            ASSERT(false)
        }

        // Attach the Shader and Free Allocated Memory
        GLCall(glAttachShader(m_Program, shader));
        GLCall(glDeleteShader(shader));
        return *this;
    }

    GLuint Shader::create(string const & filename)
    {
        auto index = filename.rfind(".");
        auto ext = filename.substr(index + 1);
        if (ext == "comp") {
            GLCall(GLuint shader = glCreateShader(GL_COMPUTE_SHADER));
            return shader;
        }
        else if (ext == "frag") {
            GLCall(GLuint shader = glCreateShader(GL_FRAGMENT_SHADER));
            return shader;
        }
        else if (ext == "geom") {
            GLCall(GLuint shader = glCreateShader(GL_GEOMETRY_SHADER));
            return shader;
        }
        else if (ext == "vert") {
            GLCall(GLuint shader = glCreateShader(GL_VERTEX_SHADER));
            return shader;
        }
        ASSERT(false)
    }

    Shader & Shader::link()
    {
        GLCall(glLinkProgram(m_Program));
        GLCall(glGetProgramiv(m_Program, GL_LINK_STATUS, & m_Status));
        if(m_Status == false)
        {
            GLCall(glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, & m_Length));
            Scope<char[]> buffer(new char[m_Length]);
            GLCall(glGetProgramInfoLog(m_Program, m_Length, nullptr, buffer.get()));
            ASSERT(false);
        }
        ASSERT(m_Status == true);
        return *this;
    }
};
