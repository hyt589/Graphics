#pragma once

#include "Core.hpp"
#include <glad/glad.h>

namespace HYT::GL
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
        ShaderProgram(Shader &shaders...);
        ~ShaderProgram();

        GLuint ID();
        bool isLinkSuccess();

    protected:
        GLuint m_id;
        bool m_linkSuccess;
    };
} // namespace HYT::GL
