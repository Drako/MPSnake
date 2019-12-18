#pragma once

#ifndef SNAKE_SDL_HELPERS_HXX
#define SNAKE_SDL_HELPERS_HXX

#include "sdl.hxx"

constexpr bool operator ==(SDL_Rect const & lhs, SDL_Rect const & rhs)
{
  return lhs.x == rhs.x
         && lhs.y == rhs.y
         && lhs.w == rhs.w
         && lhs.h == rhs.h;
}

constexpr bool operator !=(SDL_Rect const & lhs, SDL_Rect const & rhs)
{
  return lhs.x != rhs.x
         || lhs.y != rhs.y
         || lhs.w != rhs.w
         || lhs.h != rhs.h;
}

constexpr bool operator ==(SDL_Color const & lhs, SDL_Color const & rhs)
{
  return lhs.r == rhs.r
         && lhs.g == rhs.g
         && lhs.b == rhs.b
         && lhs.a == rhs.a;
}

constexpr bool operator !=(SDL_Color const & lhs, SDL_Color const & rhs)
{
  return lhs.r != rhs.r
         || lhs.g != rhs.g
         || lhs.b != rhs.b
         || lhs.a != rhs.a;
}

#ifdef CATCH_VERSION_MAJOR

#include <iomanip>
#include <sstream>

namespace Catch {
  template <>
  struct StringMaker<SDL_Rect>
  {
    static inline std::string convert(SDL_Rect const & r)
    {
      std::ostringstream os;
      os
          << "SDL_Rect "
             "{ x: " << r.x
          << ", y: " << r.y
          << ", w: " << r.w
          << ", h: " << r.h
          << " }";
      return os.str();
    }
  };


  template <>
  struct StringMaker<SDL_Color>
  {
    static inline std::string convert(SDL_Color const & c)
    {
      std::ostringstream os;
      os
          << "SDL_Color "
             "{ r: 0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c.r)
          << ", g: 0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c.g)
          << ", b: 0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c.b)
          << ", a: 0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c.a)
          << " }";
      return os.str();
    }
  };
}
#endif

#endif // SNAKE_SDL_HELPERS_HXX
