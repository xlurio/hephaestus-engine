#ifndef SPRITERENDERERITERATOR_HPP
#define SPRITERENDERERITERATOR_HPP

#include <filesystem>
#include <nlohmann/json.hpp>
#include <hph/spriterenderer.hpp>

class SpriteRendererIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = nlohmann::json;
    using pointer = const value_type *;
    using reference = const value_type &;

    SpriteRendererIterator(const nlohmann::json &sceneData, bool isEnd = false)
        : mSceneData(&sceneData), mObjectIndex(0), mComponentIndex(0)
    {
        if (isEnd)
        {
            if (sceneData.contains("objects") && sceneData["objects"].is_array())
            {
                mObjectIndex = sceneData["objects"].size();
            }
        }
        else
        {
            findNextSpriteRenderer();
        }
    }

    reference operator*()
    {
        return (*mSceneData)["objects"][mObjectIndex]["components"][mComponentIndex];
    }

    pointer operator->()
    {
        return &(*mSceneData)["objects"][mObjectIndex]["components"][mComponentIndex];
    }

    SpriteRendererIterator &operator++()
    {
        ++mComponentIndex;
        findNextSpriteRenderer();
        return *this;
    }

    SpriteRendererIterator operator++(int)
    {
        SpriteRendererIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const SpriteRendererIterator &other) const
    {
        return mSceneData == other.mSceneData &&
               mObjectIndex == other.mObjectIndex &&
               mComponentIndex == other.mComponentIndex;
    }

    bool operator!=(const SpriteRendererIterator &other) const
    {
        return !(*this == other);
    }

    SpriteRendererIterator begin() const
    {
        return SpriteRendererIterator(*mSceneData, false);
    }

    SpriteRendererIterator end() const
    {
        return SpriteRendererIterator(*mSceneData, true);
    }

private:
    bool isSpriteRenderer(const nlohmann::json &component) const
    {
        return component.contains("type") &&
               component["type"].is_string() &&
               component["type"] == "SpriteRenderer";
    }

    bool hasValidComponents(const nlohmann::json &object) const
    {
        return object.contains("components") && object["components"].is_array();
    }

    bool searchComponentsInCurrentObject(const nlohmann::json &components)
    {
        while (mComponentIndex < components.size())
        {
            if (isSpriteRenderer(components[mComponentIndex]))
            {
                return true;
            }
            ++mComponentIndex;
        }
        return false;
    }

    void findNextSpriteRenderer()
    {
        if (!mSceneData->contains("objects") || !(*mSceneData)["objects"].is_array())
        {
            mObjectIndex = 0;
            mComponentIndex = 0;
            return;
        }

        const nlohmann::json &objects = (*mSceneData)["objects"];

        while (mObjectIndex < objects.size())
        {
            const nlohmann::json &object = objects[mObjectIndex];

            if (!hasValidComponents(object))
            {
                ++mObjectIndex;
                mComponentIndex = 0;
                continue;
            }

            const nlohmann::json &components = object["components"];
            
            if (searchComponentsInCurrentObject(components))
            {
                return;
            }

            ++mObjectIndex;
            mComponentIndex = 0;
        }
    }

    const nlohmann::json *mSceneData;
    size_t mObjectIndex;
    size_t mComponentIndex;
};

#endif
