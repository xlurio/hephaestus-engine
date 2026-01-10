#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "sprite.hpp"
#include <nlohmann/json.hpp>
#include "component.hpp"
#include "transform.hpp"

class SpriteRenderer : public Component
{
public:
    Sprite sprite;

    SpriteRenderer(nlohmann::json source) : mSource(source) {}
    void render(Transform transform) {
        // TODO
    }

private:
    nlohmann::json mSource;
};

#endif