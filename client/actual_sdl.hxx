#pragma once

#ifndef SNAKE_ACTUAL_SDL_HXX
#define SNAKE_ACTUAL_SDL_HXX

#include "sdl.hxx"

namespace snake::client {
  struct ActualSDL : public SDL
  {
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
  };
}

#endif // SNAKE_ACTUAL_SDL_HXX
