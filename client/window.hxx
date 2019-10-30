#pragma once

#ifndef SNAKE_WINDOW_HXX
#define SNAKE_WINDOW_HXX

#include <stdexcept>

#include "sdl.hxx"
#include "surface.hxx"

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
    SDL & m_sdl;
    SDL_Window * m_window;

  public:
    explicit Window(SDL & sdl);

    ~Window();

    Surface getSurface();

    void update();
  };
}

#endif // SNAKE_WINDOW_HXX
