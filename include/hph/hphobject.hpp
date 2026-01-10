#ifndef HPHOBJECT_HPP
#define HPHOBJECT_HPP

#include <vector>
#include <string>
#include "linalg.hpp"

namespace hph
{
    class HphObject
    {
    protected:
        std::vector<HphObject> findGameObjectsWithTag(std::string tag)
        {
            // TODO
            return std::vector<HphObject>();
        }

        template <typename T>
        T instantiate(T original, hph::Vector3 position, hph::Quaternion rotation)
        {
            // TODO
            return original;
        }

        /**
         * `destroy` happens in runtime while `destroyImmediate` happens in edit mode
         */
        void destroy(HphObject instance, uint delay) {
            // TODO
        }
        void destroy(HphObject instance) {
            // TODO
        }
        void destroyImmediate(HphObject instance) {
            // TODO
        }

        std::vector<HphObject *> findObjectsOfType(const std::type_info &objectType)
        {
            // TODO
            return std::vector<HphObject *>();
        }
    };
}

#endif
