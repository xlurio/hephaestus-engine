#ifndef RIGIDBODY2D_HPP
#define RIGIDBODY2D_HPP

#include "behavior.hpp"
#include "linalg.hpp"

class Rigidbody2D : public Component
{
public:
    hph::Vector3 velocity;
    float mass;
    float angularVelocity;

    hph::Vector2 getPosition()
    {
        return position;
    }
    void addForce(hph::Vector2 force);
    void addTorque(float torque);

private:
    hph::Vector2 position;
};

#endif
