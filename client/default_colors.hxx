#pragma once

#ifndef SNAKE_DEFAULT_COLORS_HXX
#define SNAKE_DEFAULT_COLORS_HXX

#include "sdl.hxx"

namespace snake::client::colors {
  static SDL_Color const BLACK{0, 0, 0, 0xFF};
  static SDL_Color const WHITE{0xFF, 0xFF, 0xFF, 0xFF};

  constexpr std::uint32_t colorToRGBA(SDL_Color const & color)
  {
    return
        (static_cast<std::uint32_t>(color.r) << 24) |
        (static_cast<std::uint32_t>(color.g) << 16) |
        (static_cast<std::uint32_t>(color.b) << 8) |
        static_cast<std::uint32_t>(color.a);
  }

  constexpr SDL_Color rgbaToColor(std::uint32_t rgba)
  {
    return {
      static_cast<std::uint8_t>(rgba >> 24),
      static_cast<std::uint8_t>((rgba >> 16) & 0xFF),
      static_cast<std::uint8_t>((rgba >> 8) & 0xFF),
      static_cast<std::uint8_t>(rgba & 0xFF),
    };
  }
}

#endif // SNAKE_DEFAULT_COLORS_HXX
