#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "sprite.hpp"
#include <nlohmann/json.hpp>
#include "component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>
#include <hph/core/shader.hpp>
#include <stb_image.h>
#include <sstream>
#include <iostream>

class SpriteRenderer : public Component
{
public:
    Sprite sprite;

    SpriteRenderer(nlohmann::json source) : mSource(source) {}

    void render(Transform transform)
    {
        GLuint textureId;
        int width, height, channels;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        const char *texturePath = sprite.getPath().string().c_str();
        stbi_uc *data = stbi_load(texturePath, &width, &height, &channels, 0);

        if (data == nullptr)
            std::cerr
                << "Failed to load texture file '"
                << texturePath
                << "'"
                << std::endl;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        std::ostringstream textureVarStream;
        textureVarStream << "texture" << sprite.getId();
        mShader.setInteger(textureVarStream.str(), sprite.getId());

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, transform.position);
        modelMatrix = modelMatrix * glm::mat4_cast(transform.getRotation());
        mShader.setMatrix4f("modelMatrix", modelMatrix);
    }

private:
    nlohmann::json mSource;
    Shader mShader;
};

#endif