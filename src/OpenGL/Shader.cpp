#include "Shader.hpp"
#include "ogl_base.hpp"

namespace HYT::GL
{
    Shader::Shader(std::string path, ShaderType type)
        : m_type(type)
    {
        std::ifstream sourceFile(path);
        std::string sourceCode;
        try
        {
            std::ostringstream outstream;
            outstream << sourceFile.rdbuf();
            sourceCode = outstream.str();
        }
        catch (const std::exception &e)
        {
            LOG_ERROR("[SHADER] Error loading shader source code at {}", path);
            LOG_ERROR("[SHADER] {}", e.what());
        }
        const char *sourcePtr = sourceCode.c_str();

        GL(m_id = glCreateShader(type));
        GL(glShaderSource(m_id, 1, &sourcePtr, NULL));
        GL(glCompileShader(m_id));
        int success;
        GL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            LOG_ERROR("[SHADER] Compilation Failed: {}", path);
            char info[512];
            GL(glGetShaderInfoLog(m_id, 512, NULL, info));
            LOG_ERROR("[SHADER] {}", info);
            return;
        }
        LOG_INFO("[SHADER] Compilation Success: {}", path);
        m_isCompiled = true;
    }

    Shader::~Shader()
    {
        GL(glDeleteShader(m_id));
    }

    ShaderType Shader::getType()
    {
        return m_type;
    }

    GLuint Shader::ID()
    {
        return m_id;
    }

    bool Shader::isCompiled()
    {
        return m_isCompiled;
    }


    


} // namespace HYT::GL
