#include <catch2/catch.hpp>

#include "window.hxx"

struct SDL_Window
{
  bool destroyed;
};

TEST_CASE("Window", "[window]")
{
  using snake::client::SDL;
  using snake::client::Window;

  SECTION("auto-cleanup works")
  {
    bool create_called = false;
    SDL_Window mock_window {false};
    {
      SDL sdl;
      sdl.createWindow = [&create_called, &mock_window](char const *, int, int, int, int, std::uint32_t) {
        create_called = true;
        return &mock_window;
      };
      sdl.destroyWindow = [](SDL_Window * window) {
        window->destroyed = true;
      };

      Window const window {sdl};
    }
    REQUIRE(create_called);
    REQUIRE(mock_window.destroyed);
  }

  SECTION("constructor throws on initialization error")
  {
    bool create_called = false;
    bool destroy_called = false;
    bool exception_thrown = false;
    {
      SDL sdl;
      sdl.createWindow = [&create_called](char const *, int, int, int, int, std::uint32_t) -> SDL_Window * {
        create_called = true;
        return nullptr;
      };
      sdl.destroyWindow = [&destroy_called](SDL_Window * window) {
        destroy_called = true;
      };

      try
      {
        Window const window {sdl};
      }
      catch (Window::InitializationException const & ex)
      {
        exception_thrown = true;
      }
    }
    REQUIRE(create_called);
    REQUIRE_FALSE(destroy_called);
    REQUIRE(exception_thrown);
  }
}
