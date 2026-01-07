#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

enum KeyCode
{
    A,
    D,
    S,
    W,
    Return,
    Space,
    LeftArrow,
    UpArrow,
    RightArrow,
    DownArrow,
};

class Input
{
public:
    static bool sGetKey(KeyCode key);
    static bool sGetKeyDown(KeyCode key);
    static bool sGetMouseButtonDown(uint btnIdx);
};

#endif
