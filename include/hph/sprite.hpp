#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <filesystem>

class Sprite
{
public:
    uint getId() {
        return mId;
    }

    std::filesystem::path getPath() const
    {
        return mPath;
    }

private:
    uint mId;
    std::filesystem::path mPath;
};

#endif