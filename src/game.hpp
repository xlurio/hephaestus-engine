#ifndef GAME_HPP

#define GAME_HPP

#ifndef BASE_DIR
#define BASE_DIR "."
#endif

#include "scene.hpp"
#include <filesystem>

class Game
{
public:
    Game() : mRootPath(std::filesystem::path(BASE_DIR)),
             mCurrentScene(loadFirstScene()) {}
    void loop()
    {
    }

private:
    std::filesystem::path mRootPath;
    Scene mCurrentScene;

    Scene loadFirstScene()
    {
        std::filesystem::path scenesPath = mRootPath / "scenes";
        for (
            const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(
                scenesPath))
        {
            if (entry.is_regular_file() && entry.path().filename().string().starts_with(
                                               "0001"))
            {
                return Scene(entry.path());
            }
        }
    }

    void awake();
    void onEnable();
    void start();
    void fixedUpdate();
    void onCollisionEnter2D();
    void update();
    void onDestroy();
};

#endif
