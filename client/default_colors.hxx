#pragma once

#ifndef SNAKE_DEFAULT_COLORS_HXX
#define SNAKE_DEFAULT_COLORS_HXX

#include "sdl.hxx"

namespace snake::client::colors {
  static SDL_Color const BLACK{0, 0, 0, 0xFF};
  static SDL_Color const WHITE{0xFF, 0xFF, 0xFF, 0xFF};

  enum class Channel : std::uint8_t
  {
    Red = 0,
    Green = 8,
    Blue = 16,
    Alpha = 32,
  };

  constexpr std::uint8_t extractColorChannel(std::uint32_t color, Channel which)
  {
    return static_cast<std::uint8_t>(color >> static_cast<std::uint32_t>(which));
  }

  constexpr std::uint32_t calculateColorChannel(std::uint32_t value, Channel which)
  {
    return static_cast<std::uint32_t>(value) << static_cast<std::uint32_t>(which);
  }

  constexpr std::uint32_t colorToRGBA(SDL_Color const & color)
  {
    return
        calculateColorChannel(color.r, Channel::Red) |
        calculateColorChannel(color.g, Channel::Green) |
        calculateColorChannel(color.b, Channel::Blue) |
        calculateColorChannel(color.a, Channel::Alpha);
  }

  constexpr SDL_Color rgbaToColor(std::uint32_t rgba)
  {
    return {
        extractColorChannel(rgba, Channel::Red),
        extractColorChannel(rgba, Channel::Green),
        extractColorChannel(rgba, Channel::Blue),
        extractColorChannel(rgba, Channel::Alpha),
    };
  }
}

#endif // SNAKE_DEFAULT_COLORS_HXX
