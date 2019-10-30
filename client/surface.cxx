#include "surface.hxx"

#include <cassert>

namespace snake::client {
  Surface::InitializationException::InitializationException(char const * message)
      : std::runtime_error {message}
  {}

  Surface::Surface(snake::client::SDL & sdl, SDL_Surface * surface) noexcept
      : m_sdl {sdl}, m_surface {surface}, m_cleanUp {false}
  {
  }

  Surface::~Surface()
  {
    clear();
  }

  Surface::Surface(Surface && src) noexcept
      : m_sdl {src.m_sdl}, m_surface {src.m_surface}, m_cleanUp {src.m_cleanUp}
  {
    src.m_surface = nullptr;
  }

  Surface & Surface::operator=(Surface && src) noexcept
  {
    if (this != &src)
    {
      clear();
      m_sdl = src.m_sdl;
      m_surface = src.m_surface;
      m_cleanUp = src.m_cleanUp;
      src.m_surface = nullptr;
    }
    return *this;
  }

  void Surface::clear()
  {
    if (m_cleanUp && m_surface)
      m_sdl.freeSurface(m_surface);
    m_surface = nullptr;
  }

  void Surface::fillRect(SDL_Rect const & rect, SDL_Color color)
  {
    if (m_surface)
      m_sdl.fillRect(m_surface, &rect, m_sdl.mapRGBA(m_surface->format, color.r, color.g, color.b, color.a));
  }

  void Surface::fill(SDL_Color color)
  {
    if (m_surface)
      m_sdl.fillRect(m_surface, nullptr, m_sdl.mapRGBA(m_surface->format, color.r, color.g, color.b, color.a));
  }
}
