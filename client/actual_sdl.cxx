#include "actual_sdl.hxx"

#include <cassert>

namespace snake::client {
  int ActualSDL::init(std::uint32_t features)
  {
    assert(!SDL_WasInit(SDL_INIT_EVERYTHING));
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

  SDL_Surface * ActualSDL::getWindowSurface(SDL_Window * window)
  {
    return SDL_GetWindowSurface(window);
  }

  void ActualSDL::freeSurface(SDL_Surface * surface)
  {
    SDL_FreeSurface(surface);
  }

  int ActualSDL::fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color)
  {
    return SDL_FillRect(destination, rect, color);
  }

  std::uint32_t
  ActualSDL::mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
  {
    return SDL_MapRGBA(format, r, g, b, a);
  }

  int ActualSDL::updateWindowSurface(SDL_Window * window)
  {
    return SDL_UpdateWindowSurface(window);
  }

  std::string ActualSDL::getBasePath()
  {
    char * const basePath = SDL_GetBasePath();
    if (basePath)
    {
      std::string const result = basePath;
      SDL_free(basePath);
      return result;
    }
    else
      return "";
  }

  std::string ActualSDL::getPrefPath(char const * organizationName, char const * applicationName)
  {
    char * const prefPath = SDL_GetPrefPath(organizationName, applicationName);
    if (prefPath)
    {
      std::string const result = prefPath;
      SDL_free(prefPath);
      return result;
    }
    else
      return "";
  }

  SDL_Surface *
  ActualSDL::createRGBSurfaceWithFormat(std::uint32_t flags, int width, int height, int depth, std::uint32_t format)
  {
    return SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
  }
}
