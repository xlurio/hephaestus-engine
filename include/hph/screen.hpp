#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "behavior.hpp"
#include "linalg.hpp"

class Screen
{
public:
    static uint sGetWidth()
    {
        return sWidth;
    }

    static uint sGetHeight()
    {
        return sHeight;
    }

private:
    static uint sWidth;
    static uint sHeight;
};

#endif
