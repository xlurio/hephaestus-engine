#ifndef SCENE_HPP
#define SCENE_HPP

#include <filesystem>
#include <nlohmann/json.hpp>
#include "spriterendereriterator.hpp"
#include "gameobjectiterator.hpp"
#include <hph/gameobject.hpp>
#include <vector>

class Scene
{
public:
    Scene(std::filesystem::path sourceFile) : mGameObjects(
                                                  getGameObjectsFromSource(
                                                      sourceFile)) {}

    std::vector<GameObject> getGameObjectsFromSource(nlohmann::json sourceFile)
    {
        std::vector<GameObject> gameObjects;

        for (const GameObject &gameObject : GameObjectsSourceIterator(sourceFile))
        {
            gameObjects.push_back(gameObject);
        }

        return gameObjects;
    }

private:
    std::vector<GameObject> mGameObjects;
};

#endif
