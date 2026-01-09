#ifndef INITIALIZATION_HPP
#define INITIALIZATION_HPP

#include <SDL3/SDL.h>

SDL_Window *initSdlWindow();
SDL_GLContext initGlContext(SDL_Window *window);

#endif
