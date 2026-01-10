#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <sys/types.h>
#include <string>
#include <nlohmann/json.hpp>
#include "hphobject.hpp"
#include "component.hpp"
#include "spriterenderer.hpp"
#include "transform.hpp"

Component makeComponentFromSource(nlohmann::json source)
{
    std::string type = source["type"];
    if (type == "SpriteRenderer")
    {
        return SpriteRenderer(source);
    }
    else
    {
        return Component();
    }
}

class GameObject : public hph::HphObject
{
public:
    bool isActive;

    GameObject(nlohmann::json source)
    {
        for (nlohmann::json componentSource : source["components"])
        {
            Component component = makeComponentFromSource(componentSource);
            mComponents.push_back(&component);

            if (componentSource["type"] == "SpriteRenderer")
            {
                mRenderers.push_back(static_cast<SpriteRenderer &>(component));
            }
        }
    }

    std::vector<Component *> findGameObjectsWithTag(std::string tag) const
    {
        // TODO
        return mComponents;
    }

    void setLayer(uint newLayer)
    {
        mLayer = newLayer;
    }

    bool compareTag(std::string tag) const
    {
        // TODO
        throw 1;
    }

    std::vector<SpriteRenderer> getRenderers() const {
        return mRenderers;
    }

    Transform getTransform() const {
        return mTransform;
    }

private:
    uint mLayer;
    std::vector<Component *> mComponents;
    std::vector<SpriteRenderer> mRenderers;
    Transform mTransform;
};

#endif