#pragma once

#ifndef SNAKE_APPLICATION_HXX
#define SNAKE_APPLICATION_HXX

#include <cinttypes>
#include <functional>
#include <stdexcept>

#include "SDL.hxx"

namespace snake::client {
  class Application
  {
  public:
    class InitializationException : public std::runtime_error
    {
    public:
      explicit InitializationException(char const * message);
    };

  private:
    SDL const & m_sdl;

  public:
    explicit Application(SDL const & sdl);

    ~Application();

    [[nodiscard]]
    int run() const;
  };
}

#endif // SNAKE_APPLICATION_HXX
