#include <catch2/catch.hpp>

#include "application.hxx"

TEST_CASE("Application", "[application]")
{
  using snake::client::SDL;
  using snake::client::Application;

  SECTION("auto-cleanup works")
  {
    bool init_called = false;
    bool quit_called = false;
    {
      SDL sdl;
      sdl.init = [&init_called](std::uint32_t) {
        init_called = true;
        return 0;
      };
      sdl.quit = [&quit_called] { quit_called = true; };
      sdl.wasInit = [](std::uint32_t) -> std::uint32_t { return 1u; };

      Application const app {sdl};
    }
    REQUIRE(init_called);
    REQUIRE(quit_called);
  }

  SECTION("constructor throws on initialization error")
  {
    bool init_called = false;
    bool quit_called = false;
    bool exception_thrown = false;
    {
      SDL sdl;
      sdl.init = [&init_called](std::uint32_t) {
        init_called = true;
        return -1;
      };
      sdl.quit = [&quit_called] { quit_called = true; };
      sdl.wasInit = [](std::uint32_t) -> std::uint32_t { return 0u; };

      try
      {
        Application const app {sdl};
      }
      catch (Application::InitializationException const & ex)
      {
        exception_thrown = true;
      }
    }
    REQUIRE(init_called);
    REQUIRE_FALSE(quit_called);
    REQUIRE(exception_thrown);
  }
}
