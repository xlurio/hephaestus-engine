#ifndef MONOBEHAVIOUR_HPP
#define MONOBEHAVIOUR_HPP

#include <typeinfo>
#include <vector>
#include <stdexcept>
#include "gameobject.hpp"
#include "transform.hpp"
#include "linalg.hpp"
#include "collision2d.hpp"

class MonoBehaviour : public Behavior
{
protected:
    Component &getComponent(const std::type_info &componentClass);

    template <typename Callable>
    void invoke(Callable &&func, float time);

    template <typename Callable>
    void invokeRepeating(Callable &&func, float interval, float repeatRate);

private:
    virtual void awake();
    virtual void start();
    virtual void onEnable();
    virtual void update();
    virtual void fixedUpdate();
    virtual void onCollisionEnter2D(Collision2D collision);
    virtual void onDestroy();
};

#endif
