#include <stdlib.h>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <exception>
#include <string>
#include <sstream>
#include "initialization.hpp"
#include "exceptions.hpp"
#include "game.hpp"

#define WIDTH 800
#define HEIGHT 600
#define BASE_DIR "examples/asteroids/assets"

int main()
{
    SDL_Window *window;
    SDL_GLContext context;

    try
    {
        window = initSdlWindow();
        context = initGlContext(window);
    }
    catch (InitializationException const &exc)
    {
        SDL_LogError(exc.CATEGORY, exc.what());
        return EXIT_FAILURE;
    }

    bool shouldKeepRunning = true;
    SDL_Event event;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Game game;

    while (shouldKeepRunning)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        game.loop();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return EXIT_SUCCESS;
}
