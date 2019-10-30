#include "window.hxx"

#include <SDL2/SDL.h>

namespace snake::client {
  Window::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Window::Window(SDL & sdl)
      : m_sdl {sdl}
  {
    m_window = m_sdl.createWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED_DISPLAY(0u), SDL_WINDOWPOS_CENTERED_DISPLAY(0u),
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if (!m_window)
      throw InitializationException {m_sdl.getError()};
  }

  Window::~Window()
  {
    if (m_window)
      m_sdl.destroyWindow(m_window);
  }

  Surface Window::getSurface()
  {
    return Surface(m_sdl, m_sdl.getWindowSurface(m_window));
  }

  void Window::update()
  {
    m_sdl.updateWindowSurface(m_window);
  }
}
