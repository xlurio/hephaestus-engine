#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <hph/monobehaviour.hpp>
#include <vector>
#include <string>
#include <hph/linalg.hpp>
#include <hph/input.hpp>
#include <hph/particlesystem.hpp>
#include <hph/text.hpp>

#include "Player.hpp"
#include "Asteroid.hpp"

class GameManager : public MonoBehaviour
{
public:
    int score = 0;
    int lives = 3;

    static GameManager *sGetInstance()
    {
        return sInstance;
    };

    void onAsteroidDestroyed(Asteroid &asteroid)
    {
        explosionEffect.getTransform().position = asteroid.getTransform().position;
        explosionEffect.play();

        if (asteroid.size < 0.7f)
        {
            setScore(score + 100); // small asteroid
        }
        else if (asteroid.size < 1.4f)
        {
            setScore(score + 50); // medium asteroid
        }
        else
        {
            setScore(score + 25); // large asteroid
        }
    }

    void onPlayerDeath(Player &player)
    {
        GameObject playerGameObj = player.getGameObject();
        playerGameObj.isActive = false;

        explosionEffect.getTransform().position = player.getTransform().position;
        explosionEffect.play();

        setLives(lives - 1);

        if (lives <= 0)
        {
            gameOverUI.isActive = true;
        }
        else
        {
            invoke(respawn, player.RESPAWN_DELAY);
        }
    }

private:
    static GameManager *sInstance;
    Player &player;
    ParticleSystem explosionEffect;
    GameObject gameOverUI;
    hph::Text scoreText;
    hph::Text livesText;

    void awake()
    {
        if (sInstance != nullptr)
        {
            destroyImmediate(getGameObject());
        }
        else
        {
            sInstance = this;
        }
    }

    void onDestroy()
    {
        if (sInstance == this)
        {
            sInstance = nullptr;
        }
    }

    void start()
    {
        newGame();
    }

    void update()
    {
        if (lives <= 0 && Input::sGetKeyDown(KeyCode::Return))
        {
            newGame();
        }
    }

    void newGame()
    {
        std::vector<HphObject *> asteroids = findObjectsOfType(typeid(Asteroid));

        for (int i = 0; i < asteroids.size(); i++)
        {
            destroy(static_cast<Asteroid *>(asteroids[i])->getGameObject());
        }

        gameOverUI.isActive = false;

        setScore(0);
        setLives(3);
        respawn();
    }

    void setScore(int newScore)
    {
        score = newScore;
        scoreText.text = std::to_string(score);
    }

    void setLives(int newLives)
    {
        lives = newLives;
        livesText.text = std::to_string(lives);
    }

    void respawn()
    {
        player.getTransform().position = hph::Vector3::sMakeZero();
        GameObject playerGameObj = player.getGameObject();
        playerGameObj.isActive = true;
    }
};

#endif
