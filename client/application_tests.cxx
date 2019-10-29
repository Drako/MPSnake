#include <catch2/catch.hpp>

#include "mock_sdl.hxx"
#include "application.hxx"

TEST_CASE("Application", "[application]")
{
  using snake::client::Mock;
  using snake::client::MockSDL;
  using snake::client::Application;

  MockSDL sdl;

  SECTION("auto-cleanup works")
  {
    {
      Application const app {sdl};
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 1);
  }

  SECTION("constructor throws on initialization error")
  {
    sdl.mockFunction<Mock::Init>([](std::uint32_t) { return -1; });
    sdl.mockFunction<Mock::WasInit>([](std::uint32_t) { return 0u; });
    bool exception_thrown = false;
    {
      try
      {
        Application const app {sdl};
      }
      catch (Application::InitializationException const & ex)
      {
        exception_thrown = true;
      }
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 0);
    REQUIRE(exception_thrown);
  }
}
