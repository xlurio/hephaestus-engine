#ifndef HPHOBJECT_HPP
#define HPHOBJECT_HPP

#include "gameobject.hpp"
#include <vector>
#include <string>
#include "linalg.hpp"

namespace hph
{
    class HphObject
    {
    protected:
        std::vector<HphObject> findGameObjectsWithTag(std::string tag);

        template <typename T>
        T instantiate(T original, hph::Vector3 position, hph::Quaternion rotation);

        /**
         * `destroy` happens in runtime while `destroyImmediate` happens in edit mode
         */
        void destroy(HphObject instance, uint delay);
        void destroy(HphObject instance);
        void destroyImmediate(HphObject instance);

        std::vector<HphObject *> findObjectsOfType(const std::type_info &objectType);
    };
}

#endif
