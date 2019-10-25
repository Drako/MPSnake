#include "window.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  Window::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Window::Window(SDL const & sdl)
      : m_sdl {sdl}
  {
    m_window = m_sdl.createWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED_DISPLAY(0u), SDL_WINDOWPOS_CENTERED_DISPLAY(0u),
        WIDTH, HEIGHT,
        SDL_WINDOW_VULKAN
    );
    if (!m_window)
      throw InitializationException {m_sdl.lastError()};
  }

  Window::~Window()
  {
    if (m_window)
      m_sdl.destroyWindow(m_window);
  }
}
