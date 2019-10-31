#include <catch2/catch.hpp>

#include "mock_sdl.hxx"
#include "window.hxx"
#include "surface.hxx"

#include <limits>

TEST_CASE("Surface", "[surface]")
{
  using snake::client::Mock;
  using snake::client::MockSDL;
  using snake::client::Window;
  using snake::client::Surface;

  MockSDL sdl;

  SECTION("window surface is not freed")
  {
    // default is nullptr, which won't be freed anyways
    // thus we return a dummy pointer, to see whether that one won't be freed either
    sdl.mockFunction<Mock::GetWindowSurface>([](SDL_Window *) {
      return reinterpret_cast<SDL_Surface *>(std::numeric_limits<std::uintptr_t>::max());
    });
    {
      Window window{sdl};
      Surface screen = window.getSurface();
    }
    REQUIRE(sdl.getCallCount(Mock::GetWindowSurface) == 1);
    REQUIRE(sdl.getCallCount(Mock::FreeSurface) == 0);
  }
}
