#pragma once

#ifndef SNAKE_ACTUAL_SDL_HXX
#define SNAKE_ACTUAL_SDL_HXX

#include "sdl.hxx"

#include <functional>
#include <map>
#include <tuple>

namespace snake::client {
  static SDL_Window * const MOCK_WINDOW = (SDL_Window *)(std::uintptr_t)(~0u);

  enum class Mock : unsigned long
  {
    Init,
    Quit,
    WasInit,
    GetError,
    CreateWindow,
    DestroyWindow
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
        MockFunction<Mock::DestroyWindow>
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

    int init(std::uint32_t features) override;

    void quit() override;

    char const * getError() override;

    std::uint32_t wasInit(std::uint32_t features) override;

    SDL_Window * createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags) override;

    void destroyWindow(SDL_Window * window) override;
  };
}

#endif // SNAKE_ACTUAL_SDL_HXX
