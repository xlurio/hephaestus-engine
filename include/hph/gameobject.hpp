#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include "component.hpp"
#include <sys/types.h>
#include <string>
#include "hphobject.hpp"

class GameObject: public hph::HphObject
{
public:
    bool isActive;

    std::vector<GameObject> findGameObjectsWithTag(std::string tag);

    void setLayer(uint newLayer)
    {
        layer = newLayer;
    }

    bool compareTag(std::string tag);

private:
    uint layer;
    std::vector<Component *> components;
};

#endif