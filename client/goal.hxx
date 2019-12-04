#pragma once

#ifndef SNAKE_GOAL_HXX
#define SNAKE_GOAL_HXX

#include "game_object.hxx"

namespace snake::client {
  class Goal : public GameObject
  {
    SDL_Rect m_area;

  public:
    Goal(SDL_Rect const & area, SDL & sdl);

    void render(Surface & renderTarget) const override;

    void moveTo(SDL_Rect const & area);

    [[nodiscard]]
    SDL_Rect const & area() const;
  };
}

#endif // SNAKE_GOAL_HXX
