#pragma once

#ifndef SNAKE_GAME_OBJECT_HXX
#define SNAKE_GAME_OBJECT_HXX

#include "sdl.hxx"
#include "surface.hxx"

namespace snake::client {
  class GameObject
  {
  protected:
    SDL & m_sdl;

  public:
    explicit GameObject(SDL & sdl);

    virtual ~GameObject() = default;

    virtual bool update(double elapsedTime);

    virtual void render(Surface & renderTarget) const = 0;
  };
}

#endif // SNAKE_GAME_OBJECT_HXX
