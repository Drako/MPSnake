#include <catch2/catch.hpp>

#include "mock_sdl.hxx"
#include "window.hxx"

TEST_CASE("Window", "[window]")
{
  using snake::client::Mock;
  using snake::client::MockSDL;
  using snake::client::Window;

  MockSDL sdl;

  SECTION("auto-cleanup works")
  {
    {
      Window const window {sdl};
    }
    REQUIRE(sdl.getCallCount(Mock::CreateWindow) == 1);
    REQUIRE(sdl.getCallCount(Mock::DestroyWindow) == 1);
  }

  SECTION("constructor throws on initialization error")
  {
    sdl.mockFunction<Mock::CreateWindow>([](char const *, int, int, int, int, std::uint32_t) -> SDL_Window * {
      return nullptr;
    });
    bool exception_thrown = false;
    {
      try
      {
        Window const window {sdl};
      }
      catch (Window::InitializationException const & ex)
      {
        exception_thrown = true;
      }
    }
    REQUIRE(sdl.getCallCount(Mock::CreateWindow) == 1);
    REQUIRE(sdl.getCallCount(Mock::DestroyWindow) == 0);
    REQUIRE(exception_thrown);
  }
}
