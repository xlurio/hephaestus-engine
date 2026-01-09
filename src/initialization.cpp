#include <stdlib.h>
#include <SDL3/SDL.h>
#include <sstream>
#include "exceptions.hpp"
#include <glad/glad.h>

#ifndef WIDTH
#define WIDTH 640  // Redefine to set the window width
#endif

#ifndef HEIGHT
#define HEIGHT 480 // Redefine to set the window height
#endif

SDL_Window *initSdlWindow()
{
    setenv("WAYLAND_DISPLAY", "", 1);
    setenv("XDG_SESSION_TYPE", "x11", 1);

    SDL_SetAppMetadata("Hephaestus", "0.1.0alpha", "com.calegario.hephaestus");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "Couldn't initialize SDL: " << SDL_GetError();
        throw InitializationException(errorMsgStream.str());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow(
        "Hephaestus",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL);

    if (!window)
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "Couldn't create window: " << SDL_GetError();
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        throw InitializationException(errorMsgStream.str());
    }

    return window;
}

SDL_GLContext initGlContext(SDL_Window *window)
{
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!context)
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "Couldn't create OpenGL context: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
        throw InitializationException(errorMsgStream.str());
    }

    if (!SDL_GL_MakeCurrent(window, context))
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "Couldn't make set OpenGL context as current: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
        throw InitializationException(errorMsgStream.str());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "Couldn't initialize GLAD: " << SDL_GetError();
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
        throw InitializationException(errorMsgStream.str());
    }
}