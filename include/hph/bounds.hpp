#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include "linalg.hpp"

class Bounds
{
public:
    hph::Vector3 getMax() {
        return max;
    }
    hph::Vector3 getMin() {
        return min;
    }

    void encapsulate(hph::Vector3 point);

private:
    hph::Vector3 max;
    hph::Vector3 min;
};

#endif