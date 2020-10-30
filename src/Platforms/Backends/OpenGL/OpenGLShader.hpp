#pragma once

#include "Core.hpp"
#include "gl_base.hpp"

namespace HYT::OpenGL
{
    // enum GlShaderType
    // {
    //     vertex = GL_VERTEX_SHADER,
    //     tessControl = GL_TESS_CONTROL_SHADER,
    //     tessEvaluation = GL_TESS_EVALUATION_SHADER,
    //     geometry = GL_GEOMETRY_SHADER,
    //     fragment = GL_FRAGMENT_SHADER,
    //     compute = GL_COMPUTE_SHADER
    // };

    class Shader : public ::HYT::Graphics::Shader
    {
        public:
        Shader(std::initializer_list<::HYT::Graphics::ShaderSrc> & shaders);
        virtual void bind() const override;
        virtual void unbind() const override;
    };
    
} // namespace HYT::OpenGL
