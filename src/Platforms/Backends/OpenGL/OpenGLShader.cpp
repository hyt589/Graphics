#include "OpenGLShader.hpp"
#include <magic_enum.hpp>

namespace HYT::OpenGL
{
    using ::HYT::Graphics::ShaderType;

    static constexpr GLenum GLShaderType(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::vertex:
            return GL_VERTEX_SHADER;
            break;
        case ShaderType::tessControl:
            return GL_TESS_CONTROL_SHADER;
            break;
        case ShaderType::tessEvaluation:
            return GL_TESS_EVALUATION_SHADER;
            break;
        case ShaderType::geometry:
            return GL_GEOMETRY_SHADER;
            break;
        case ShaderType::fragment:
            return GL_FRAGMENT_SHADER;
            break;
        case ShaderType::compute:
            return GL_COMPUTE_SHADER;
            break;
        }
    }

    Shader::Shader(std::initializer_list<::HYT::Graphics::ShaderSrc> &shaders)
    {
        GL(m_id = glCreateProgram());
        std::vector<uint32_t> shaderIds;
        for (auto &shader : shaders)
        {
            uint32_t _shader_id = GL(glCreateShader(GLShaderType(shader.getType())));
            const char *_src_code = shader.getSource();
            GL(glShaderSource(_shader_id, 1, &_src_code, NULL));
            GL(glCompileShader(_shader_id));
            int success;
            GL(glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &success));
            if (!success)
            {
                char info[512];
                GL(glGetShaderInfoLog(_shader_id, 512, NULL, info));
                LOG_ERROR("[OpenGL] Shader compilation failed: {}", shader.getPath());
                LOG_ERROR("[OpenGL] {}", info);
                GL(glDeleteShader(_shader_id));
                continue;
            }
            LOG_INFO("[OpenGL] Shader compilation success: {}", shader.getPath());
            GL(glAttachShader(m_id, _shader_id));
            shaderIds.push_back(_shader_id);
        }
        GL(glLinkProgram(m_id));
        int success;
        GL(glGetProgramiv(m_id, GL_LINK_STATUS, &success));
        if (!success)
        {
            char info[512];
            GL(glGetProgramInfoLog(m_id, 512, NULL, info));
            LOG_ERROR("[OpenGL] Shader linking failed");
            LOG_ERROR("[OpenGL] {}", info);
            GL(glDeleteProgram(m_id));
            return;
        }
        LOG_INFO("[OpenGL] Shader linking success");
        for (auto id : shaderIds)
        {
            GL(glDetachShader(m_id, id));
            GL(glDeleteShader(id));
        }
    }

    void Shader::bind() const
    {
        GL(glUseProgram(m_id));
    }

    void Shader::unbind() const
    {
        GL(glUseProgram(0));
    }

    void Shader::setUniform(std::string name, std::any value)
    {
        GL(glUseProgram(m_id));
        auto loc = GL(glGetUniformLocation(m_id, name.c_str()));
        if (loc == -1)
        {
            LOG_ERROR("[OpenGL] Uniform {} not found");
            GL(glUseProgram(0));
            return;
        }
        if (value.type() == typeid(int))
        {
            GL(glUniform1i(loc, std::any_cast<int>(value)));
        }
        else if (value.type() == typeid(float))
        {
            GL(glUniform1f(loc, std::any_cast<float>(value)));
        }
        else if (value.type() == typeid(double))
        {
            GL(glUniform1d(loc, std::any_cast<double>(value)));
        }
        else if (value.type() == typeid(glm::vec3))
        {
            GL(glUniform3fv(loc, 1, glm::value_ptr(std::any_cast<glm::vec3>(value))));
        }
        else if (value.type() == typeid(glm::vec4))
        {
            GL(glUniform4fv(loc, 1, glm::value_ptr(std::any_cast<glm::vec4>(value))));
        }
        else if (value.type() == typeid(glm::mat4))
        {
            GL(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat4>(value))));
        }
        else
        {
            LOG_ERROR("[OpenGL] Unknown type for shader uniform {}", name);
        }
        GL(glUseProgram(0));
    }
} // namespace HYT::OpenGL
