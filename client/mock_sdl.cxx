#include "mock_sdl.hxx"

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
    return impl ? impl(title, x, y, w, h, flags) : MOCK_WINDOW;
  }

  void MockSDL::destroyWindow(SDL_Window * window)
  {
    ++m_callCounts[Mock::DestroyWindow];
    auto const & impl = getMock<Mock::DestroyWindow>().impl;
    if (impl) impl(window);
  }
}
