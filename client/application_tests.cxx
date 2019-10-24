#include <catch2/catch.hpp>

#include "application.hxx"

using snake::client::Application;

TEST_CASE("Application", "[application]")
{
  SECTION("auto-cleanup works")
  {
    bool init_called = false;
    bool quit_called = false;
    {
      Application const app {
          [&init_called](std::uint32_t) {
            init_called = true;
            return 0;
          },
          [&quit_called] { quit_called = true; }
      };
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
      try
      {
        Application const app {
            [&init_called](std::uint32_t) {
              init_called = true;
              return -1;
            },
            [&quit_called] { quit_called = true; }
        };
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
