#include "mock_sdl.hxx"
#include "native.hxx"
#include "default_colors.hxx"

#include <cassert>
#include <filesystem>

struct SDL_Window
{
  char const * title;
  int x, y, w, h;
  std::uint32_t flags;
  SDL_DisplayMode mode;
};

namespace snake::client {
  template <MockPolicy policy>
  int MockSDL<policy>::getCallCount(Mock mock) const
  {
    auto const it = m_callCounts.find(mock);
    return it == m_callCounts.end() ? 0 : it->second;
  }

  template <MockPolicy policy>
  int MockSDL<policy>::init(std::uint32_t features)
  {
    ++m_callCounts[Mock::Init];
    auto const & impl = getMock<Mock::Init>().impl;
    if (impl) return impl(features);
    else if constexpr (policy == MockPolicy::Stub) return 0;
    else return ActualSDL::init(features);
  }

  template <MockPolicy policy>
  void MockSDL<policy>::quit()
  {
    ++m_callCounts[Mock::Quit];
    auto const & impl = getMock<Mock::Quit>().impl;
    if (impl) impl();
    else if constexpr (policy == MockPolicy::CallOriginal) ActualSDL::quit();
  }

  template <MockPolicy policy>
  char const * MockSDL<policy>::getError()
  {
    ++m_callCounts[Mock::GetError];
    auto const & impl = getMock<Mock::GetError>().impl;
    if (impl) return impl();
    else if constexpr (policy == MockPolicy::Stub) return "";
    else return ActualSDL::getError();
  }

  template <MockPolicy policy>
  std::uint32_t MockSDL<policy>::wasInit(std::uint32_t features)
  {
    ++m_callCounts[Mock::WasInit];
    auto const & impl = getMock<Mock::WasInit>().impl;
    if (impl) return impl(features);
    else if constexpr (policy == MockPolicy::Stub) return features;
    else return ActualSDL::wasInit(features);
  }

  template <MockPolicy policy>
  SDL_Window * MockSDL<policy>::createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags)
  {
    ++m_callCounts[Mock::CreateWindow];
    auto const & impl = getMock<Mock::CreateWindow>().impl;
    if (impl) return impl(title, x, y, w, h, flags);
    else if constexpr (policy == MockPolicy::Stub) return new SDL_Window{title, x, y, w, h, flags};
    else return ActualSDL::createWindow(title, x, y, w, h, flags);
  }

  template <MockPolicy policy>
  void MockSDL<policy>::destroyWindow(SDL_Window * window)
  {
    ++m_callCounts[Mock::DestroyWindow];
    auto const & impl = getMock<Mock::DestroyWindow>().impl;
    if (impl) impl(window);
    else if constexpr (policy == MockPolicy::Stub) delete window;
    else ActualSDL::destroyWindow(window);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::setWindowDisplayMode(SDL_Window * window, SDL_DisplayMode const * mode)
  {
    ++m_callCounts[Mock::SetWindowDisplayMode];
    auto const & impl = getMock<Mock::SetWindowDisplayMode>().impl;
    if (impl)
      return impl(window, mode);
    else if constexpr (policy == MockPolicy::Stub)
    {
      assert(window != nullptr);
      assert(mode != nullptr);
      window->mode = *mode;
      return 0;
    }
    else
      return ActualSDL::setWindowDisplayMode(window, mode);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::getWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode)
  {
    ++m_callCounts[Mock::GetWindowDisplayMode];
    auto const & impl = getMock<Mock::GetWindowDisplayMode>().impl;
    if (impl)
      return impl(window, mode);
    else if constexpr (policy == MockPolicy::Stub)
    {
      assert(window != nullptr);
      assert(mode != nullptr);
      *mode = window->mode;
      return 0;
    }
    else
      return ActualSDL::getWindowDisplayMode(window, mode);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::pollEvent(SDL_Event * event)
  {
    ++m_callCounts[Mock::PollEvent];
    auto const & impl = getMock<Mock::PollEvent>().impl;
    if (impl)
      return impl(event);
    else if constexpr (policy == MockPolicy::Stub)
    {
      assert(event != nullptr);
      return 0;
    }
    else
      return ActualSDL::pollEvent(event);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::pushEvent(SDL_Event * event)
  {
    ++m_callCounts[Mock::PushEvent];
    auto const & impl = getMock<Mock::PushEvent>().impl;
    if (impl)
      return impl(event);
    else if constexpr (policy == MockPolicy::Stub)
    {
      assert(event != nullptr);
      return 0;
    }
    else
      return ActualSDL::pushEvent(event);
  }

  template <MockPolicy policy>
  void MockSDL<policy>::useEventQueue(std::deque<SDL_Event> & queue)
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

  SDL_Event event_helpers::makeQuitEvent(std::uint32_t timestamp)
  {
    SDL_Event result{};
    result.quit = SDL_QuitEvent{SDL_QUIT, timestamp};
    return result;
  }

  template <MockPolicy policy>
  SDL_Surface * MockSDL<policy>::getWindowSurface(SDL_Window * window)
  {
    ++m_callCounts[Mock::GetWindowSurface];
    auto const & impl = getMock<Mock::GetWindowSurface>().impl;
    if (impl)
      return impl(window);
    else if constexpr (policy == MockPolicy::Stub)
    {
      assert(window != nullptr);
      return nullptr;
    }
    else
      return ActualSDL::getWindowSurface(window);
  }

  template <MockPolicy policy>
  void MockSDL<policy>::freeSurface(SDL_Surface * surface)
  {
    ++m_callCounts[Mock::FreeSurface];
    auto const & impl = getMock<Mock::FreeSurface>().impl;
    if (impl) impl(surface);
    else if constexpr (policy == MockPolicy::CallOriginal) ActualSDL::freeSurface(surface);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color)
  {
    ++m_callCounts[Mock::FillRect];
    auto const & impl = getMock<Mock::FillRect>().impl;
    if (impl) return impl(destination, rect, color);
    else if constexpr (policy == MockPolicy::Stub) return 0;
    else return ActualSDL::fillRect(destination, rect, color);
  }

  template <MockPolicy policy>
  uint32_t
  MockSDL<policy>::mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b,
                           std::uint8_t a)
  {
    ++m_callCounts[Mock::MapRGBA];
    auto const & impl = getMock<Mock::MapRGBA>().impl;
    if (impl) return impl(format, r, g, b, a);
    else if constexpr (policy == MockPolicy::Stub) return colors::colorToRGBA({r, g, b, a});
    else return ActualSDL::mapRGBA(format, r, g, b, a);
  }

  template <MockPolicy policy>
  int MockSDL<policy>::updateWindowSurface(SDL_Window * window)
  {
    ++m_callCounts[Mock::UpdateWindowSurface];
    auto const & impl = getMock<Mock::UpdateWindowSurface>().impl;
    if (impl) return impl(window);
    else if constexpr (policy == MockPolicy::Stub) return 0;
    else return ActualSDL::updateWindowSurface(window);
  }

  template <MockPolicy policy>
  std::string MockSDL<policy>::getBasePath()
  {
    ++m_callCounts[Mock::GetBasePath];
    auto const & impl = getMock<Mock::GetBasePath>().impl;
    if (impl) return impl();
    else if constexpr (policy == MockPolicy::Stub) return native::getExePath().parent_path();
    else return ActualSDL::getBasePath();
  }

  template <MockPolicy policy>
  std::string MockSDL<policy>::getPrefPath(char const * organizationName, char const * applicationName)
  {
    ++m_callCounts[Mock::GetPrefPath];
    auto const & impl = getMock<Mock::GetPrefPath>().impl;
    if (impl) return impl(organizationName, applicationName);
    else if constexpr (policy == MockPolicy::Stub) return std::filesystem::temp_directory_path();
    else return ActualSDL::getPrefPath(organizationName, applicationName);
  }

  template <MockPolicy policy>
  SDL_Surface * MockSDL<policy>::createRGBSurfaceWithFormat(std::uint32_t flags, int width, int height, int depth,
                                                            std::uint32_t format)
  {
    ++m_callCounts[Mock::CreateRGBSurfaceWithFormat];
    auto const & impl = getMock<Mock::CreateRGBSurfaceWithFormat>().impl;
    if (impl) return impl(flags, width, height, depth, format);
    else if constexpr (policy == MockPolicy::Stub) return nullptr;
    else return ActualSDL::createRGBSurfaceWithFormat(flags, width, height, depth, format);
  }

  template
  class MockSDL<MockPolicy::Stub>;

  template
  class MockSDL<MockPolicy::CallOriginal>;
}
