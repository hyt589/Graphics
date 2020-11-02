#pragma once

#include <glad/glad.h>
#include "Core.hpp"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

/**
 * @brief Check if an error occurred within OpenGL
 * 
 * @param file the file name where the error is located
 * @param line the line number where the error is located
 * @return true if an error has been detected
 * @return false if no error has been detected
 */
inline bool glCheckError_(const char * file, int line)
{
    bool err = false;
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        LOG_ERROR("{} occurred at {}, line {}", __FILE__, __LINE__);
        err = true;
    }
    return err;
}

/**
 * @brief Check if an OpenGL error has occurred
 * 
 */
#define glCheckError if(glCheckError_(__FILE__, __LINE__)) std::raise(SIGINT)

#if HYT_DEBUG
/**
 * @brief Debug wrapper around OpenGL functions
 * 
 */
#define GL(glFunctionCall) glFunctionCall; glCheckError
#else
#define GL(glFunctionCall) glFunctionCall
#endif