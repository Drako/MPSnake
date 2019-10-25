#pragma once

#ifndef SNAKE_SDL_HXX
#define SNAKE_SDL_HXX

#include <cstdint>

#include <functional>

struct SDL_Window;

namespace snake::client {
  /**
   * @brief Helper to make the SDL mockable.
   */
  struct SDL
  {
    std::function<int(std::uint32_t)> init;
    std::function<void()> quit;
    std::function<char const *()> getError;
    std::function<std::uint32_t(std::uint32_t)> wasInit;
    std::function<SDL_Window *(char const *, int, int, int, int, std::uint32_t)> createWindow;
    std::function<void(SDL_Window *)> destroyWindow;

    [[nodiscard]]
    inline char const * lastError() const
    {
      return getError ? getError() : "(unknown error)";
    }
  };
}

#endif // SNAKE_SDL_HXX
