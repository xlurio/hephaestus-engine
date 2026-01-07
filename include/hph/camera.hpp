#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "behavior.hpp"
#include "linalg.hpp"

class Camera
{
public:
    static Camera sGetMain()
    {
        return sMain;
    }
    hph::Vector3 screenToWorldPoint(hph::Vector3 position);

private:
    static Camera sMain;
};

#endif
