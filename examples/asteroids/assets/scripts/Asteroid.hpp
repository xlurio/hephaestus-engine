#include <hph/monobehaviour.hpp>
#include <hph/linalg.hpp>
#include <hph/rigidbody2d.hpp>
#include <hph/spriterenderer.hpp>
#include <hph/sprite.hpp>
#include <hph/random.hpp>
#include <vector>
#include <cstdlib>

#include "GameManager.hpp"

class Asteroid : public MonoBehaviour
{
public:
    float size = 1.0f;
    float minSize = 0.35f;
    float maxSize = 1.65f;
    float movementSpeed = 50.0f;
    float maxLifetime = 30.0f;

    void setTrajectory(hph::Vector2 direction)
    {
        // The asteroid only needs a force to be added once since they have no
        // drag to make them stop moving
        rigidBody.addForce(direction * movementSpeed);
    }

private:
    Rigidbody2D &rigidBody;
    SpriteRenderer &spriteRenderer;
    std::vector<Sprite> sprites;

    void awake()
    {
        rigidBody = (Rigidbody2D &)getComponent(typeid(Rigidbody2D));
        spriteRenderer = (SpriteRenderer &)getComponent(typeid(SpriteRenderer));
    }

    void start()
    {
        // Assign random properties to make each asteroid feel unique
        spriteRenderer.sprite = sprites[hph::generateInRange(0ul, sprites.size())];
        getTransform().eulerAngles = hph::Vector3(0.0f, 0.0f, hph::normalizedRandomNumber() * 360.0f);

        // Set the scale and mass of the asteroid based on the assigned size so
        // the physics is more realistic
        getTransform().localScale = hph::Vector3::sMakeOne() * size;
        rigidBody.mass = size;

        // Destroy the asteroid after it reaches its max lifetime
        destroy(getGameObject(), maxLifetime);
    }

    void onCollisionEnter2D(Collision2D collision)
    {
        if (collision.getGameObject().compareTag("Bullet"))
        {
            // Check if the asteroid is large enough to split in half
            // (both parts must be greater than the minimum size)
            if ((size * 0.5f) >= minSize)
            {
                createSplit();
                createSplit();
            }

            GameManager::sGetInstance()->onAsteroidDestroyed(*this);

            // Destroy the current asteroid since it is either replaced by two
            // new asteroids or small enough to be destroyed by the bullet
            destroy(getGameObject());
        }
    }
    Asteroid createSplit()
    {
        // Set the new asteroid poistion to be the same as the current asteroid
        // but with a slight offset so they do not spawn inside each other
        hph::Vector2 position = getTransform().position;
        position += hph::generateInsideUnitCircle() * 0.5f;

        // Create the new asteroid at half the size of the current
        Asteroid *half = instantiate(this, position, getTransform().getRotation());
        half->size = size * 0.5f;

        // Set a random trajectory
        half->setTrajectory(hph::generateInsideUnitCircle());

        return *half;
    }
};