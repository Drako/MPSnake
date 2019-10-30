#pragma once

#ifndef SNAKE_ACTUAL_SDL_HXX
#define SNAKE_ACTUAL_SDL_HXX

#include "sdl.hxx"

#include <deque>
#include <functional>
#include <map>
#include <tuple>

namespace snake::client {
  enum class Mock : unsigned long
  {
    Init,
    Quit,
    WasInit,
    GetError,
    CreateWindow,
    DestroyWindow,
    SetWindowDisplayMode,
    GetWindowDisplayMode,
    PollEvent,
    PushEvent,
    GetWindowSurface,
    FreeSurface,
    FillRect,
    MapRGBA,
    UpdateWindowSurface
  };

  template <Mock mock>
  struct MockTraits;

  template <>
  struct MockTraits<Mock::Init>
  {
    using Signature = int(std::uint32_t);
  };

  template <>
  struct MockTraits<Mock::Quit>
  {
    using Signature = void();
  };

  template <>
  struct MockTraits<Mock::WasInit>
  {
    using Signature = std::uint32_t(std::uint32_t);
  };

  template <>
  struct MockTraits<Mock::GetError>
  {
    using Signature = char const *();
  };

  template <>
  struct MockTraits<Mock::CreateWindow>
  {
    using Signature = SDL_Window *(char const * title, int x, int y, int w, int h, std::uint32_t flags);
  };

  template <>
  struct MockTraits<Mock::DestroyWindow>
  {
    using Signature = void(SDL_Window *);
  };

  template <>
  struct MockTraits<Mock::SetWindowDisplayMode>
  {
    using Signature = int(SDL_Window *, SDL_DisplayMode const *);
  };

  template <>
  struct MockTraits<Mock::GetWindowDisplayMode>
  {
    using Signature = int(SDL_Window *, SDL_DisplayMode *);
  };

  template <>
  struct MockTraits<Mock::PollEvent>
  {
    using Signature = int(SDL_Event *);
  };

  template <>
  struct MockTraits<Mock::PushEvent>
  {
    using Signature = int(SDL_Event *);
  };

  template <>
  struct MockTraits<Mock::GetWindowSurface>
  {
    using Signature = SDL_Surface *(SDL_Window *);
  };

  template <>
  struct MockTraits<Mock::FreeSurface>
  {
    using Signature = void(SDL_Surface *);
  };

  template <>
  struct MockTraits<Mock::FillRect>
  {
    using Signature = int(SDL_Surface *, SDL_Rect const *, std::uint32_t);
  };

  template <>
  struct MockTraits<Mock::MapRGBA>
  {
    using Signature = std::uint32_t(SDL_PixelFormat const *, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t);
  };

  template <>
  struct MockTraits<Mock::UpdateWindowSurface>
  {
    using Signature = int(SDL_Window *);
  };

  template <Mock mock>
  using MockSignature = typename MockTraits<mock>::Signature;
  template <Mock mock>
  struct MockFunction
  {
    std::function<MockSignature<mock>> impl;
  };

  class MockSDL : public SDL
  {
    std::map<Mock, int> m_callCounts;

    std::tuple<
        MockFunction<Mock::Init>,
        MockFunction<Mock::Quit>,
        MockFunction<Mock::WasInit>,
        MockFunction<Mock::GetError>,
        MockFunction<Mock::CreateWindow>,
        MockFunction<Mock::DestroyWindow>,
        MockFunction<Mock::SetWindowDisplayMode>,
        MockFunction<Mock::GetWindowDisplayMode>,
        MockFunction<Mock::PollEvent>,
        MockFunction<Mock::PushEvent>,
        MockFunction<Mock::GetWindowSurface>,
        MockFunction<Mock::FreeSurface>,
        MockFunction<Mock::FillRect>,
        MockFunction<Mock::MapRGBA>,
        MockFunction<Mock::UpdateWindowSurface>
    > m_mocks;

    template <Mock mock>
    inline MockFunction<mock> & getMock()
    {
      return std::get<static_cast<std::underlying_type_t<Mock>>(mock)>(m_mocks);
    }

  public:
    [[nodiscard]]
    int getCallCount(Mock mock) const;

    template <Mock mock>
    inline void mockFunction(std::function<MockSignature<mock>> impl)
    {
      getMock<mock>().impl = std::move(impl);
    }

    static SDL_Window * makeMockWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags);

    static SDL_Event makeQuitEvent(std::uint32_t timestamp = 0u);

    void useEventQueue(std::deque<SDL_Event> & queue);

    int init(std::uint32_t features) override;

    void quit() override;

    char const * getError() override;

    std::uint32_t wasInit(std::uint32_t features) override;

    SDL_Window * createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags) override;

    void destroyWindow(SDL_Window * window) override;

    int setWindowDisplayMode(SDL_Window * window, SDL_DisplayMode const * mode) override;

    int getWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode) override;

    int pollEvent(SDL_Event * event) override;

    int pushEvent(SDL_Event * event) override;

    SDL_Surface * getWindowSurface(SDL_Window * window) override;

    void freeSurface(SDL_Surface * surface) override;

    virtual int fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color) override;

    virtual uint32_t
    mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) override;

    virtual int updateWindowSurface(SDL_Window * window) override;
  };
}

#endif // SNAKE_ACTUAL_SDL_HXX
