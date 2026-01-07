#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <hph/monobehaviour.hpp>
#include <hph/rigidbody2d.hpp>
#include <hph/gameobject.hpp>
#include <hph/bounds.hpp>
#include <hph/linalg.hpp>
#include <hph/camera.hpp>
#include <hph/screen.hpp>
#include <hph/input.hpp>
#include <hph/collision2d.hpp>
#include <hph/layermask.hpp>

#include "Bullet.hpp"
#include "GameManager.hpp"

class Player : public MonoBehaviour
{

public:
    const float THRUST_MAGNITUDE = 1.0f;
    const float ROTATION_SPEED = 0.1f;
    const float RESPAWN_DELAY = 3.0f;
    const float RESPAWN_INVULNERABILITY = 3.0f;

    bool thrusting;
    bool screenWrapping = true;

private:
    Rigidbody2D &rigidBody;
    Bullet bulletPrefab;
    float turnDirection;
    Bounds screenBounds;

    void awake()
    {
        rigidBody = (Rigidbody2D &)getComponent(typeid(Rigidbody2D));
    }

    void start()
    {
        screenBounds.encapsulate(Camera::sGetMain().screenToWorldPoint(hph::Vector3::sMakeZero()));
        screenBounds.encapsulate(Camera::sGetMain().screenToWorldPoint(hph::Vector3(
            Screen::sGetWidth,
            Screen::sGetHeight,
            0.0f)));
    }

    void onEnable()
    {
        // Turn off collisions for a few seconds after spawning to ensure the
        // player has enough time to safely move away from asteroids
        turnOffCollisions();
        invoke(turnOnCollisions, RESPAWN_INVULNERABILITY);
    }

    void update()
    {
        thrusting = Input::sGetKey(KeyCode::W) || Input::sGetKey(KeyCode::UpArrow);

        if (Input::sGetKey(KeyCode::A) || Input::sGetKey(KeyCode::LeftArrow))
        {
            turnDirection = 1.0f;
        }
        else if (Input::sGetKey(KeyCode::D) || Input::sGetKey(KeyCode::RightArrow))
        {
            turnDirection = -1.0f;
        }
        else
        {
            turnDirection = 0.0f;
        }

        if (Input::sGetKeyDown(KeyCode::Space) || Input::sGetMouseButtonDown(0))
        {
            shoot();
        }
    }

    void fixedUpdate()
    {
        if (thrusting)
        {
            rigidBody.addForce(getTransform().getUp() * THRUST_MAGNITUDE);
        }

        if (turnDirection != 0.0f)
        {
            rigidBody.addTorque(ROTATION_SPEED * turnDirection);
        }

        if (screenWrapping)
        {
            screenWrap();
        }
    }

    void screenWrap()
    {
        // Move to the opposite side of the screen if the player exceeds the bounds
        if (rigidBody.getPosition().x > screenBounds.getMax().x + 0.5f)
        {
            rigidBody.getPosition() = hph::Vector2(
                screenBounds.getMin().x - 0.5f,
                rigidBody.getPosition().y);
        }
        else if (rigidBody.getPosition().x < screenBounds.getMin().x - 0.5f)
        {
            rigidBody.getPosition() = hph::Vector2(
                screenBounds.getMax().x + 0.5f,
                rigidBody.getPosition().y);
        }
        else if (rigidBody.getPosition().y > screenBounds.getMax().y + 0.5f)
        {
            rigidBody.getPosition() = hph::Vector2(
                rigidBody.getPosition().x,
                screenBounds.getMin().y - 0.5f);
        }
        else if (rigidBody.getPosition().y < screenBounds.getMin().y - 0.5f)
        {
            rigidBody.getPosition() = hph::Vector2(
                rigidBody.getPosition().x,
                screenBounds.getMax().y + 0.5f);
        }
    }

    void shoot()
    {
        Bullet bullet = instantiate(
            bulletPrefab, getTransform().position,
            getTransform().getRotation());
        bullet.shoot(getTransform().getUp());
    }

    void turnOffCollisions()
    {
        getGameObject().setLayer(
            hph::LayerMask::sGetLayerFromName("Ignore Collisions"));
    }

    void turnOnCollisions()
    {
        getGameObject().setLayer(hph::LayerMask::sGetLayerFromName("Player"));
    }

    void onCollisionEnter2D(Collision2D collision)
    {
        if (collision.getGameObject().compareTag("Asteroid"))
        {
            rigidBody.velocity = hph::Vector3::sMakeZero();
            rigidBody.angularVelocity = 0.0f;

            GameManager::sGetInstance()->onPlayerDeath(*this);
        }
    }
};

#endif
