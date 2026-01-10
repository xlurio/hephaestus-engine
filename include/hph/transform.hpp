#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "linalg.hpp"

class Transform
{
public:
    hph::Vector3 position;
    hph::Vector3 eulerAngles;
    hph::Vector3 localScale;

    hph::Quaternion getRotation() const
    {
        return mRotation;
    }

    hph::Vector3 getUp();

private:
    hph::Quaternion mRotation;
};

#endif
