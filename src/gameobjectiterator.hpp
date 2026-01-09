#ifndef GAMEOBJECTRENDERER_HPP
#define GAMEOBJECTRENDERER_HPP

#include <iterator>
#include <optional>
#include <hph/gameobject.hpp>

class GameObjectsSourceIterator
{
private:
    class Iterator
    {
        using iterator_category = std::input_iterator_tag;
        using value_type = GameObject;
        using difference_type = std::ptrdiff_t;
        using reference = const value_type &;
        using pointer = const value_type *;

    public:
        Iterator(nlohmann::json source, uint index) : mSource(source), mIndex(index) {}

        Iterator &operator++()
        {
            findNextGameObject();
            return *this;
        }

        Iterator operator++(int)
        {
            ++*this;
        }

        reference operator*() const
        {
            return GameObject(mSource["objects"][mIndex]);
        }

        pointer operator->() const
        {
            return &GameObject(mSource["objects"][mIndex]);
        }

        bool operator==(const Iterator &other) const
        {
            return mSource == other.mSource &&
                   mIndex == other.getIndex();
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

        uint getIndex() const
        {
            return mIndex;
        }

    private:
        nlohmann::json mSource;
        uint mIndex = 0;

        void findNextGameObject()
        {
            uint newIndex = mIndex + 1;

            if (newIndex < mSource["objects"].size())
                mIndex = newIndex;
        }
    };

public:
    GameObjectsSourceIterator(nlohmann::json source) : mSource(source)
    {
    }

    Iterator begin() const
    {
        return Iterator(mSource, false);
    }

    Iterator end() const
    {
        return Iterator(mSource, true);
    }

private:
    nlohmann::json mSource;
};

#endif
