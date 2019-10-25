#include "application.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  Application::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Application::Application(SDL const & sdl)
      : m_sdl {sdl}
  {
    if (m_sdl.init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
      throw InitializationException {m_sdl.getError ? m_sdl.getError() : ""};
  }

  Application::~Application()
  {
    if (m_sdl.wasInit(SDL_INIT_EVERYTHING) != 0u)
      m_sdl.quit();
  }

  int Application::run() const
  {
    return 0;
  }
}
