#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "gameobject.hpp"

class Behavior: public Component
{
public:
    GameObject getGameObject()
    {
        return gameObject;
    }

private:
    GameObject gameObject;
};

#endif