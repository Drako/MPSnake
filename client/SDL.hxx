#pragma once

#ifndef SNAKE_SDL_HXX
#define SNAKE_SDL_HXX

#include <cstdint>

#include <functional>

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
  };
}

#endif // SNAKE_SDL_HXX
