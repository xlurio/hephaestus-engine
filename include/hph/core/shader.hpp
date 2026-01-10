#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Shader
{
public:
    void setInteger(const std::string variableName, int value)
    {
        glUniform1i(
            glGetUniformLocation(mProgramId, variableName.c_str()),
            value);
    }

    void setMatrix4f(const std::string variableName, glm::mat4 value)
    {
        glUniformMatrix4fv(
            glGetUniformLocation(mProgramId, variableName.c_str()),
            1,
            GL_FALSE,
            glm::value_ptr(value));
    }

private:
    GLuint mProgramId;
};

#endif
