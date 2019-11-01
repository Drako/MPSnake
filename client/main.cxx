#ifdef SNAKE_TESTING
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#else // !SNAKE_TESTING

#define SDL_MAIN_HANDLED
#include "application.hxx"
#include "actual_sdl.hxx"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else

int main()
#endif
{
  SDL_SetMainReady();
  snake::client::ActualSDL sdl;
  snake::client::Application app {sdl};
  return app.run();
}

#endif
