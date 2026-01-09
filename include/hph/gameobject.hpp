#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include "component.hpp"
#include <sys/types.h>
#include <string>
#include "hphobject.hpp"
#include <nlohmann/json.hpp>
#include <hph/spriterenderer.hpp>

class GameObject : public hph::HphObject
{
public:
    bool isActive;

    GameObject(nlohmann::json source) : mJsonSource(source) {}

    std::vector<Component *> findGameObjectsWithTag(std::string tag)
    {
        return mComponents;
    }

    void setLayer(uint newLayer)
    {
        layer = newLayer;
    }

    bool compareTag(std::string tag) {
        throw 1;
    }

private:
    uint layer;
    std::vector<Component *> mComponents;
    std::vector<SpriteRenderer> mRenderers;
    nlohmann::json mJsonSource;
};

#endif