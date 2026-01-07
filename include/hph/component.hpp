#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "hphobject.hpp"
#include "transform.hpp"

class Component : public hph::HphObject
{
public:
    Transform getTransform()
    {
        return transform;
    }

private:
    Transform transform;
};

#endif