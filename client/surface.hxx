#pragma once

#ifndef SNAKE_SURFACE_HXX
#define SNAKE_SURFACE_HXX

#include <stdexcept>

#include "sdl.hxx"

namespace snake::client {
  class Surface
  {
  public:
    class InitializationException : public std::runtime_error
    {
    public:
      explicit InitializationException(char const * message);
    };

  private:
    SDL & m_sdl;
    SDL_Surface * m_surface;
    bool m_cleanUp;

  public:
    Surface(SDL & sdl, SDL_Surface * surface) noexcept;
    Surface(SDL & sdl, int width, int height);

    ~Surface();

    Surface(Surface const &) = delete;

    Surface & operator =(Surface const &) = delete;

    Surface(Surface && src) noexcept;

    [[nodiscard]]
    SDL_Surface * getRaw() const noexcept;

    void fillRect(SDL_Rect const & rect, SDL_Color color);

    void fill(SDL_Color color);
  };
}

#endif // SNAKE_SURFACE_HXX
