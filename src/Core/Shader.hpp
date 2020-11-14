#pragma once

#include "global.hpp"
#include "Log.hpp"

namespace HYT::Graphics
{

    enum class ShaderType
    {
        vertex,
        tessControl,
        tessEvaluation,
        geometry,
        fragment,
        compute
    };

    class ShaderSrc
    {
    public:
        ShaderSrc(std::string path, ShaderType shaderType)
            : m_shaderType(shaderType), m_path(path)
        {
            std::ifstream srcInStream(path);
            std::ostringstream srcOutStream;
            try
            {
                srcOutStream << srcInStream.rdbuf();
                m_src = srcOutStream.str();
                LOG_INFO("[SHADER] {} loaded", path);
            }
            catch (const std::exception &e)
            {
                LOG_ERROR("[SHADER] failed to load {}", path);
                LOG_ERROR("[SHADER] {}", e.what());
            }
        };

        ShaderSrc(ShaderType shaderType, std::string src)
            : m_path(""), m_shaderType(shaderType), m_src(src){};

        inline const char *getSource() const
        {
            return m_src.c_str();
        };

        inline std::string getPath() const
        {
            return m_path;
        };

        ShaderType getType() const
        {
            return m_shaderType;
        };

        static ShaderSrc *load(std::string path, ShaderType shaderType);

    protected:
        std::string m_src;
        std::string m_path;
        ShaderType m_shaderType;
    };

    class Shader
    {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setUniform(std::string name, std::any value) = 0;
        inline void bindAndDo(std::function<void()> task)
        {
            bind();
            task();
            unbind();
        };

        static Shared<Shader> create(std::initializer_list<ShaderSrc> l);

    protected:
        uint32_t m_id;
    };
} // namespace HYT::Graphics
