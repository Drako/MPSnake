#include "actual_sdl.hxx"

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

  int ActualSDL::setWindowDisplayMode(SDL_Window * window, SDL_DisplayMode const * mode)
  {
    return SDL_SetWindowDisplayMode(window, mode);
  }

  int ActualSDL::getWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode)
  {
    return SDL_GetWindowDisplayMode(window, mode);
  }

  int ActualSDL::pollEvent(SDL_Event * event)
  {
    return SDL_PollEvent(event);
  }

  int ActualSDL::pushEvent(SDL_Event * event)
  {
    return SDL_PushEvent(event);
  }
}
