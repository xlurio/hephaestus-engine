#ifndef LAYERMASK_HPP
#define LAYERMASK_HPP

#include "gameobject.hpp"
#include <vector>
#include <string>
#include "linalg.hpp"

typedef unsigned int HphLayerId;

namespace hph
{
    class LayerMask
    {
    public:
        static HphLayerId sGetLayerFromName(std::string layerName);
    };
}

#endif
