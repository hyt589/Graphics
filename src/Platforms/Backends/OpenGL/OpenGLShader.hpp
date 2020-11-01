#pragma once

#include "Core.hpp"
#include "gl_base.hpp"

namespace HYT::OpenGL
{

    class Shader : public ::HYT::Graphics::Shader
    {
        public:
        Shader(std::initializer_list<::HYT::Graphics::ShaderSrc> & shaders);
        virtual void bind() const override;
        virtual void unbind() const override;
    };
    
} // namespace HYT::OpenGL
