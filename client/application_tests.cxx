#include <catch2/catch.hpp>

#include "mock_sdl.hxx"
#include "application.hxx"

TEST_CASE("Application", "[application]")
{
  using namespace snake::client;
  using namespace snake::client::event_helpers;

  MockSDL sdl;

  SECTION("auto-cleanup works")
  {
    {
      Application const app{sdl};
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 1);
  }

  SECTION("constructor throws on initialization error")
  {
    sdl.mockFunction<Mock::Init>([](std::uint32_t) { return -1; });
    sdl.mockFunction<Mock::WasInit>([](std::uint32_t) { return 0u; });
    bool exception_thrown = false;
    try
    {
      Application const app{sdl};
    }
    catch (Application::InitializationException const & ex)
    {
      exception_thrown = true;
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 0);
    REQUIRE(exception_thrown);
  }

  SECTION("application quits on SDL_QUIT event")
  {
    std::deque<SDL_Event> events{makeQuitEvent()};

    sdl.useEventQueue(events);

    Application app{sdl};
    auto const exitCode = app.run();
    REQUIRE(exitCode == 0);
  }

  SECTION("auto-cleanup should also work if base path could not be determined")
  {
    sdl.mockFunction<Mock::GetBasePath>([] { return ""; });
    bool exception_thrown = false;
    try
    {
      Application const app{sdl};
    }
    catch (Application::InitializationException const & ex)
    {
      exception_thrown = true;
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 1);
    REQUIRE(sdl.getCallCount(Mock::GetBasePath) == 1);
    REQUIRE(exception_thrown);
  }

  SECTION("auto-cleanup should also work if pref path could not be determined")
  {
    sdl.mockFunction<Mock::GetPrefPath>([](char const *, char const *) { return ""; });
    bool exception_thrown = false;
    try
    {
      Application const app{sdl};
    }
    catch (Application::InitializationException const & ex)
    {
      exception_thrown = true;
    }
    REQUIRE(sdl.getCallCount(Mock::Init) == 1);
    REQUIRE(sdl.getCallCount(Mock::Quit) == 1);
    REQUIRE(sdl.getCallCount(Mock::GetPrefPath) == 1);
    REQUIRE(exception_thrown);
  }
}
