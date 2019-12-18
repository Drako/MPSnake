#include <catch2/catch.hpp>

#include "mock_sdl.hxx"
#include "sdl_helpers.hxx"
#include "surface.hxx"
#include "goal.hxx"
#include "default_colors.hxx"

#include <limits>

TEST_CASE("Goal", "[goal][gameobject]")
{
  using namespace snake::client;

  MockSDL sdl;

  sdl.init(SDL_INIT_VIDEO);

  SECTION("goal renders correctly")
  {
    Surface surface{sdl, 32, 32};
    Goal const goal{{1, 1, 10, 10}, sdl};

    sdl.mockFunction<Mock::FillRect>([&](SDL_Surface * target, SDL_Rect const * area, std::uint32_t color) {
      REQUIRE(target == surface.getRaw());
      REQUIRE(colors::rgbaToColor(color) == colors::WHITE);
      REQUIRE(*area == goal.area());
      return 0;
    });

    goal.render(surface);

    REQUIRE(sdl.getCallCount(Mock::FillRect) == 1);
  }

  SECTION("goal can be moved")
  {
    SDL_Rect const expected = {2, 2, 10, 10};
    Goal goal{{1, 1, 10, 10}, sdl};
    goal.moveTo(expected);
    REQUIRE(goal.area() == expected);
  }

  sdl.quit();
}
