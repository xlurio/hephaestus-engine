#include <hph/monobehaviour.hpp>
#include <hph/linalg.hpp>
#include <hph/random.hpp>

#include "Asteroid.hpp"

class AsteroidSpawner : public MonoBehaviour
{
public:
    Asteroid asteroidPrefab;
    float spawnDistance = 12.0f;
    float spawnRate = 1.0f;
    int amountPerSpawn = 1.0;
    float trajectoryVariance = 15.0f;

    void Spawn()
    {
        for (int i = 0; i < amountPerSpawn; i++)
        {
            // Choose a random direction from the center of the spawner and
            // spawn the asteroid a distance away
            hph::Vector3 spawnDirection = hph::generateInsideUnitCircle();
            hph::Vector3 spawnPoint = getTransform().position + (spawnDirection * spawnDistance);

            // Calculate a random variance in the asteroid's rotation which will
            // cause its trajectory to change
            float variance = hph::generateInRange(-trajectoryVariance, trajectoryVariance);
            hph::Quaternion rotation = hph::Quaternion::sAngleAxis(variance, hph::Vector3::sMakeForward());

            // Create the new asteroid by cloning the prefab and set a random
            // size within the range
            Asteroid asteroid = instantiate(asteroidPrefab, spawnPoint, rotation);
            asteroid.size = hph::generateInRange(asteroid.minSize, asteroid.maxSize);

            // Set the trajectory to move in the direction of the spawner
            hph::Vector2 trajectory = rotation * -spawnDirection;
            asteroid.setTrajectory(trajectory);
        }
    }

private:
    void Start()
    {
        invokeRepeating(Spawn, spawnRate, spawnRate);
    }
};
