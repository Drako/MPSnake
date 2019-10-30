#include "mock_sdl.hxx"

#include <cassert>

struct SDL_Window
{
  char const * title;
  int x, y, w, h;
  std::uint32_t flags;
  SDL_DisplayMode mode;
};

namespace snake::client {
  int MockSDL::getCallCount(Mock mock) const
  {
    auto const it = m_callCounts.find(mock);
    return it == m_callCounts.end() ? 0 : it->second;
  }

  int MockSDL::init(std::uint32_t features)
  {
    ++m_callCounts[Mock::Init];
    auto const & impl = getMock<Mock::Init>().impl;
    return impl ? impl(features) : 0;
  }

  void MockSDL::quit()
  {
    ++m_callCounts[Mock::Quit];
    auto const & impl = getMock<Mock::Quit>().impl;
    if (impl) impl();
  }

  char const * MockSDL::getError()
  {
    ++m_callCounts[Mock::GetError];
    auto const & impl = getMock<Mock::GetError>().impl;
    return impl ? impl() : "";
  }

  std::uint32_t MockSDL::wasInit(std::uint32_t features)
  {
    ++m_callCounts[Mock::WasInit];
    auto const & impl = getMock<Mock::WasInit>().impl;
    return impl ? impl(features) : features;
  }

  SDL_Window * MockSDL::createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags)
  {
    ++m_callCounts[Mock::CreateWindow];
    auto const & impl = getMock<Mock::CreateWindow>().impl;
    return impl ? impl(title, x, y, w, h, flags) : makeMockWindow(title, x, y, w, h, flags);
  }

  void MockSDL::destroyWindow(SDL_Window * window)
  {
    ++m_callCounts[Mock::DestroyWindow];
    auto const & impl = getMock<Mock::DestroyWindow>().impl;
    if (impl)
      impl(window);
    else
      delete window;
  }

  SDL_Window * MockSDL::makeMockWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags)
  {
    return new SDL_Window {title, x, y, w, h, flags};
  }

  int MockSDL::setWindowDisplayMode(SDL_Window * window, SDL_DisplayMode const * mode)
  {
    ++m_callCounts[Mock::SetWindowDisplayMode];
    auto const & impl = getMock<Mock::SetWindowDisplayMode>().impl;
    if (impl)
      return impl(window, mode);
    else
    {
      assert(window != nullptr);
      assert(mode != nullptr);
      window->mode = *mode;
      return 0;
    }
  }

  int MockSDL::getWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode)
  {
    ++m_callCounts[Mock::GetWindowDisplayMode];
    auto const & impl = getMock<Mock::GetWindowDisplayMode>().impl;
    if (impl)
      return impl(window, mode);
    else
    {
      assert(window != nullptr);
      assert(mode != nullptr);
      *mode = window->mode;
      return 0;
    }
  }

  int MockSDL::pollEvent(SDL_Event * event)
  {
    ++m_callCounts[Mock::PollEvent];
    auto const & impl = getMock<Mock::PollEvent>().impl;
    if (impl)
      return impl(event);
    else
    {
      assert(event != nullptr);
      return 0;
    }
  }

  int MockSDL::pushEvent(SDL_Event * event)
  {
    ++m_callCounts[Mock::PushEvent];
    auto const & impl = getMock<Mock::PushEvent>().impl;
    if (impl)
      return impl(event);
    else
    {
      assert(event != nullptr);
      return 0;
    }
  }

  void MockSDL::useEventQueue(std::deque<SDL_Event> & queue)
  {
    mockFunction<Mock::PushEvent>([&queue](SDL_Event * event) {
      assert(event != nullptr);
      queue.push_back(*event);
      return 1;
    });

    mockFunction<Mock::PollEvent>([&queue](SDL_Event * event) {
      assert(event != nullptr);
      if (queue.empty())
        return 0;
      else
      {
        *event = queue.front();
        queue.pop_front();
        return 1;
      }
    });
  }

  SDL_Event MockSDL::makeQuitEvent(std::uint32_t timestamp)
  {
    SDL_Event result {};
    result.quit = SDL_QuitEvent {SDL_QUIT, timestamp};
    return result;
  }

  SDL_Surface * MockSDL::getWindowSurface(SDL_Window * window)
  {
    ++m_callCounts[Mock::GetWindowSurface];
    auto const & impl = getMock<Mock::GetWindowSurface>().impl;
    if (impl)
      return impl(window);
    else
    {
      assert(window != nullptr);
      return nullptr;
    }
  }

  void MockSDL::freeSurface(SDL_Surface * surface)
  {
    ++m_callCounts[Mock::FreeSurface];
    auto const & impl = getMock<Mock::FreeSurface>().impl;
    if (impl)
      impl(surface);
  }

  int MockSDL::fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color)
  {
    ++m_callCounts[Mock::FillRect];
    auto const & impl = getMock<Mock::FillRect>().impl;
    return impl ? impl(destination, rect, color) : 0;
  }

  uint32_t
  MockSDL::mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
  {
    ++m_callCounts[Mock::MapRGBA];
    auto const & impl = getMock<Mock::MapRGBA>().impl;
    if (impl)
      return impl(format, r, g, b, a);
    else
    {
      assert(format != nullptr);
      return SDL_MapRGBA(format, r, g, b, a);
    }
  }

  int MockSDL::updateWindowSurface(SDL_Window * window)
  {
    ++m_callCounts[Mock::UpdateWindowSurface];
    auto const & impl = getMock<Mock::UpdateWindowSurface>().impl;
    return impl ? impl(window) : 0;
  }
}
