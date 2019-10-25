#ifdef SNAKE_TESTING
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#else // !SNAKE_TESTING

#include "application.hxx"

#include <SDL2/SDL.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else

int main()
#endif
{
  snake::client::SDL sdl;
  sdl.init = &SDL_Init;
  sdl.quit = &SDL_Quit;
  sdl.getError = &SDL_GetError;
  sdl.wasInit = &SDL_WasInit;
  snake::client::Application app {sdl};
  return app.run();
}

#endif
