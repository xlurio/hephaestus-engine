#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace hph
{
    class Vector2 : public glm::vec2
    {
    public:
        using glm::vec2::vec2;

        Vector2(const glm::vec2 &v) : glm::vec2(v) {}
    };

    class Vector3 : public glm::vec3
    {
    public:
        using glm::vec3::vec3;

        Vector3(const glm::vec3 &v) : glm::vec3(v) {}
        Vector3(const Vector2 &v) : glm::vec3(v.x, v.y, 0.0f) {}

        static Vector3 sMakeZero();
        static Vector3 sMakeOne();
        static Vector3 sMakeForward();
    };

    class Quaternion : public glm::quat
    {
    public:
        using glm::quat::quat;

        Quaternion(const glm::quat &v) : glm::quat(v) {}

        static hph::Quaternion sAngleAxis(float variance, hph::Vector3) {
            return glm::angleAxis(variance, glm::vec3(variance));
        }
    };
}

#endif