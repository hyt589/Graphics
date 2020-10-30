#include "OpenGLShader.hpp"
#include <magic_enum.hpp>

namespace HYT::OpenGL
{
    using ::HYT::Graphics::ShaderType;

    static const std::unordered_map<ShaderType, GLenum> shaderTypeMap = {
        {ShaderType::vertex, GL_VERTEX_SHADER},
        {ShaderType::tessControl, GL_TESS_CONTROL_SHADER},
        {ShaderType::tessEvaluation, GL_TESS_EVALUATION_SHADER},
        {ShaderType::geometry, GL_GEOMETRY_SHADER},
        {ShaderType::fragment, GL_FRAGMENT_SHADER},
        {ShaderType::compute, GL_COMPUTE_SHADER}
    };

    Shader::Shader(std::initializer_list<::HYT::Graphics::ShaderSrc> & shaders)
    {
        GL(m_id = glCreateProgram());
        std::vector<uint32_t> shaderIds;
        for (auto &shader : shaders)
        {
            uint32_t _shader_id = GL(glCreateShader(shaderTypeMap.at(shader.getType())));
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
        for(auto id : shaderIds)
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
} // namespace HYT::OpenGL
