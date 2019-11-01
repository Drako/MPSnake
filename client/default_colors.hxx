#pragma once

#ifndef SNAKE_DEFAULT_COLORS_HXX
#define SNAKE_DEFAULT_COLORS_HXX

#include "sdl.hxx"

namespace snake::client::colors {
  static SDL_Color const BLACK { 0, 0, 0, 0xFF };
  static SDL_Color const WHITE { 0xFF, 0xFF, 0xFF, 0xFF };
}

#endif // SNAKE_DEFAULT_COLORS_HXX
