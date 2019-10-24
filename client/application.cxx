#include "application.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  Application::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Application::Application(Init const & init, Quit quit, GetError getError)
      : m_getError {std::move(getError)}
  {
    if (init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0)
      m_quit = std::move(quit);
    else
      throw InitializationException {getError ? getError() : ""};
  }

  Application::~Application()
  {
    if (m_quit)
      m_quit();
  }

  int Application::run() const
  {
    return 0;
  }
}
