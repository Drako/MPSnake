#include "application.hxx"
#include "window.hxx"
#include "default_colors.hxx"
#include "goal.hxx"

namespace snake::client {
  Application::InitializationException::InitializationException(char const * message)
      : std::runtime_error{message}
  {}

  Application::Application(SDL & sdl)
      : m_sdl{sdl}
  {
    try
    {
      if (m_sdl.init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
        throw InitializationException{m_sdl.getError()};

      m_basePath = m_sdl.getBasePath();
      if (m_basePath.empty())
        throw InitializationException{m_sdl.getError()};

      m_prefPath = m_sdl.getPrefPath("drako.guru", "snake");
      if (m_prefPath.empty())
        throw InitializationException{m_sdl.getError()};
    }
    catch (...)
    {
      if (m_sdl.wasInit(SDL_INIT_EVERYTHING) != 0u)
        m_sdl.quit();

      throw;
    }
  }

  Application::~Application()
  {
    m_sdl.quit();
  }

  int Application::run() const
  {
    Window window{m_sdl};
    Surface screen = window.getSurface();
    Goal const goal{{1, 1, 10, 10}, m_sdl};

    for (bool running = true; running;)
    {
      screen.fill(colors::BLACK);
      goal.render(screen);
      window.update();

      for (SDL_Event event{}; m_sdl.pollEvent(&event);)
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
