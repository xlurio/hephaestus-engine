#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <glm/glm.hpp>
#include <cmath>
#include "linalg.hpp"

namespace hph
{
    float normalizedRandomNumber()
    {
        std::random_device randomSeed;
        std::mt19937 randomGenerator(randomSeed());
        return static_cast<float>(randomGenerator()) / static_cast<float>(randomGenerator.max());
    }

    hph::Vector2 generateInsideUnitCircle()
    {
        int angle = glm::radians(normalizedRandomNumber() * 2 * M_PI);
        return hph::Vector2(cos(angle), sin(angle));
    }

    template <typename NumericType>
    NumericType generateInRange(NumericType floor, NumericType ceil)
    {
        return floor + normalizedRandomNumber() * (ceil - floor);
    }
}

#endif
