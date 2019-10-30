#include "application.hxx"
#include "window.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  Application::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Application::Application(SDL & sdl)
      : m_sdl {sdl}
  {
    if (m_sdl.init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
      throw InitializationException {m_sdl.getError()};
  }

  Application::~Application()
  {
    if (m_sdl.wasInit(SDL_INIT_EVERYTHING) != 0u)
      m_sdl.quit();
  }

  int Application::run() const
  {
    Window window {m_sdl};
    SDL_Event event {};
    bool running = true;
    while (running)
    {
      while (m_sdl.pollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          running = false;
          break;
        }
      }
    }
    return 0;
  }
}
