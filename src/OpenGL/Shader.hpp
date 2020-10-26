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

    /**
     * @brief OpenGL shader abstraction
     * 
     */
    class Shader
    {
    public:
        /**
         * @brief Construct a new Shader object
         * 
         * @param path path to the shader file
         * @param type type of the shader
         */
        Shader(std::string path, ShaderType type);
        ~Shader();

        /**
         * @brief Get the ID of the shader
         * 
         * @return GLuint id
         */
        GLuint ID();

        /**
         * @brief Get the type if the shader
         * 
         * @return ShaderType 
         */
        ShaderType getType();

        /**
         * @brief check if the shader is compiled
         * 
         * @return true 
         * @return false 
         */
        bool isCompiled();

    protected:
        GLuint m_id;
        ShaderType m_type;
        bool m_isCompiled = false;
    };

    /**
     * @brief OpenGL program abstraction
     * 
     */
    class ShaderProgram
    {
    public:
        /**
         * @brief Construct a new Shader Program object
         * 
         * @param shader shaders to be linked
         */
        ShaderProgram(Shader *shader ...);
        ~ShaderProgram();

        GLuint ID();
        bool isLinkSuccess();

        void activate();
        void deactivate();

        /**
         * @brief Perform some tasks with the program being active
         * 
         * @param f the task to be performed
         */
        void activateAndDo(std::function<void()> f);

        /**
         * @brief Set the Uniform
         * 
         * @tparam T type of the uniform variable
         * @param name name of the uniform variable
         * @param value value to assign to the uniform variable
         * @param f glUniform function to call
         */
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

        /**
         * @brief Set the Uniform
         * 
         * @tparam T type of the uniform variable
         * @tparam P type of the value pointer
         * @param name name of the uniform variable
         * @param value value to assign to the uniform variable
         * @param f glUniform function to call
         */
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

        /**
         * @brief Set the Uniform
         * 
         * @tparam T type of the uniform variable
         * @tparam P type of the value pointer
         * @param name name of the uniform variable
         * @param value value to assign to the uniform variable
         * @param f glUniform function to call
         */
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
