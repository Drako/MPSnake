#pragma once

#ifndef SNAKE_APPLICATION_HXX
#define SNAKE_APPLICATION_HXX

#include <cinttypes>
#include <functional>
#include <stdexcept>

namespace snake::client {
  class Application
  {
  public:
    class InitializationException : public std::runtime_error
    {
    public:
      explicit InitializationException(char const * message);
    };

    using Init = std::function<int(std::uint32_t)>;
    using Quit = std::function<void()>;
    using GetError = std::function<char const *()>;

  private:
    Quit m_quit = nullptr;
    GetError m_getError;

  public:
    Application(Init const & init, Quit quit, GetError getError = nullptr);

    ~Application();

    int run() const;
  };
}

#endif // SNAKE_APPLICATION_HXX
