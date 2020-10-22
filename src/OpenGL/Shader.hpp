#pragma once

#include "ogl_base.hpp"

namespace HYT::OpenGL
{
    enum ShaderType
    {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        TessCtl = GL_TESS_CONTROL_SHADER,
        TessEval = GL_TESS_EVALUATION_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    class Shader
    {
    public:
        Shader(std::string path, ShaderType);
        ~Shader();

        GLuint ID();
        ShaderType getType();
        bool isCompiled();

    protected:
        GLuint m_id;
        ShaderType m_type;
        bool m_isCompiled = false;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram(Shader *shader, ...);
        ~ShaderProgram();

        GLuint ID();
        bool isLinkSuccess();

        void activate();
        void deactivate();

        void activateAndDo(std::function<void()> f);

        template <typename T>
        void setUniform(std::string name, T value, void (*f)(GLint, T))
        {
            activate();
            auto loc = GL(glGetUniformLocation(m_id, name.c_str()));
            if (loc == -1)
            {
                LOG_ERROR("[OpenGL] Uniform not found: {}", name);
                deactivate();
                return;
            }
            GL((*f)(loc, value));
            deactivate();
        };

        template <typename T, typename P>
        void setUniform(std::string name, T value, void (*f)(GLint, GLsizei, P))
        {
            activate();
            auto loc = GL(glGetUniformLocation(m_id, name.c_str()));
            if (loc == -1)
            {
                LOG_ERROR("[OpenGL] Uniform not found: {}", name);
                deactivate();
                return;
            }
            GL((*f)(loc, 1, glm::value_ptr(value)));
            deactivate();
        };

        template <typename T, typename P>
        void setUniform(std::string name, T value, void (*f)(GLint, GLsizei, GLboolean, P))
        {
            activate();
            auto loc = GL(glGetUniformLocation(m_id, name.c_str()));
            if (loc == -1)
            {
                LOG_ERROR("[OpenGL] Uniform not found: {}", name);
                deactivate();
                return;
            }
            GL((*f)(loc, 1, GL_FALSE, glm::value_ptr(value)));
            deactivate();
        };

    protected:
        GLuint m_id;
        bool m_linkSuccess = false;
    };
} // namespace HYT::OpenGL
