#ifndef BULLET_HPP
#define BULLET_HPP

#include <hph/monobehaviour.hpp>
#include <hph/linalg.hpp>
#include <hph/rigidbody2d.hpp>
#include <hph/collision2d.hpp>

class Bullet : public MonoBehaviour
{
public:
    float forceMagnitude = 500.0f;

    float maxLifetime = 10.0f;

    void shoot(hph::Vector2 direction)
    {
        rigidBody.addForce((hph::Vector2)(direction * forceMagnitude));

        destroy(getGameObject(), maxLifetime);
    }

private:
    Rigidbody2D &rigidBody;

    void awake()
    {
        rigidBody = (Rigidbody2D &)getComponent(typeid(Rigidbody2D));
    }

    void onCollisionEnter2D(Collision2D collision)
    {
        destroy(getGameObject());
    }
};

#endif
