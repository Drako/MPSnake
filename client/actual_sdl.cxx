#include "actual_sdl.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  int ActualSDL::init(std::uint32_t features)
  {
    return SDL_Init(features);
  }

  void ActualSDL::quit()
  {
    SDL_Quit();
  }

  std::uint32_t ActualSDL::wasInit(std::uint32_t features)
  {
    return SDL_WasInit(features);
  }

  char const * ActualSDL::getError()
  {
    return SDL_GetError();
  }

  SDL_Window * ActualSDL::createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags)
  {
    return SDL_CreateWindow(title, x, y, w, h, flags);
  }

  void ActualSDL::destroyWindow(SDL_Window * window)
  {
    SDL_DestroyWindow(window);
  }
}
