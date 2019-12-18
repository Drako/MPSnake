#include "game_object.hxx"

namespace snake::client {
  GameObject::GameObject(snake::client::SDL & sdl)
      : m_sdl{sdl}
  {}

  bool GameObject::update(double)
  {
    return true;
  }
}
