#include "Shader.hpp"

namespace HYT::OpenGL
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
            LOG_ERROR("[OpenGL] Error loading shader source code at {}", path);
            LOG_ERROR("[OpenGL] {}", e.what());
        }
        const char *sourcePtr = sourceCode.c_str();

        GL(m_id = glCreateShader(type));
        GL(glShaderSource(m_id, 1, &sourcePtr, NULL));
        GL(glCompileShader(m_id));
        int success;
        GL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            LOG_ERROR("[OpenGL] Compilation Failed: {}", path);
            char info[512];
            GL(glGetShaderInfoLog(m_id, 512, NULL, info));
            LOG_ERROR("[OpenGL] {}", info);
            return;
        }
        LOG_INFO("[OpenGL] Compilation Success: {}", path);
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

    ShaderProgram::ShaderProgram(Shader *shader, ...)
    {
        GL(m_id = glCreateProgram());
        va_list shaders;
        va_start(shaders, shader);
        GL(glAttachShader(m_id, va_arg(shaders, Shader *)->ID()));
        LOG_INFO("[OpenGL] shader {} attached to {}", va_arg(shaders, Shader *)->ID(), m_id);
        va_end(shaders);

        GL(glLinkProgram(m_id));
        int success;
        GL(glGetProgramiv(m_id, GL_LINK_STATUS, &success));
        if (!success)
        {
            LOG_ERROR("[OpenGL] Link Error");
            char info[512];
            GL(glGetProgramInfoLog(m_id, 512, NULL, info));
            LOG_ERROR("[OpenGL] {}", info);
            return;
        }
        LOG_INFO("[OpenGL] Program {} link success", m_id);
        m_linkSuccess = true;
    }

    ShaderProgram::~ShaderProgram()
    {
        GL(glDeleteProgram(m_id));
    }

    void ShaderProgram::activate()
    {
        GL(glUseProgram(m_id));
    }

    void ShaderProgram::deactivate()
    {
        GL(glUseProgram(0));
    }

    void ShaderProgram::activateAndDo(std::function<void()> f)
    {
        activate();
        f();
        deactivate();
    }

} // namespace HYT::OpenGL
