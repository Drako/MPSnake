#include "goal.hxx"
#include "default_colors.hxx"

namespace snake::client {
  Goal::Goal(SDL_Rect const & area, snake::client::SDL & sdl)
      : GameObject{sdl}, m_area{area}
  {}

  void Goal::render(Surface & renderTarget) const
  {
    renderTarget.fillRect(m_area, colors::WHITE);
  }

  void Goal::moveTo(SDL_Rect const & area)
  {
    m_area = area;
  }

  SDL_Rect const & Goal::area() const
  {
    return m_area;
  }
}
