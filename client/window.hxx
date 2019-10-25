#pragma once

#ifndef SNAKE_WINDOW_HXX
#define SNAKE_WINDOW_HXX

#include <stdexcept>

#include "SDL.hxx"

namespace snake::client {
  class Window
  {
  public:
    class InitializationException : public std::runtime_error
    {
    public:
      explicit InitializationException(char const * message);
    };

    static int const WIDTH = 800;
    static int const HEIGHT = 600;

  private:
    SDL const & m_sdl;
    SDL_Window * m_window;

  public:
    explicit Window(SDL const & sdl);

    ~Window();
  };
}

#endif // SNAKE_WINDOW_HXX
