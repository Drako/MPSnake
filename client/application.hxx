#pragma once

#ifndef SNAKE_APPLICATION_HXX
#define SNAKE_APPLICATION_HXX

#include <stdexcept>

#include "sdl.hxx"

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
    SDL & m_sdl;

  public:
    explicit Application(SDL & sdl);

    ~Application();

    [[nodiscard]]
    int run() const;
  };
}

#endif // SNAKE_APPLICATION_HXX
