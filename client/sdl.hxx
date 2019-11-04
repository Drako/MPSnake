#pragma once

#ifndef SNAKE_SDL_HXX
#define SNAKE_SDL_HXX

#include <cstdint>
#include <string>

#include <SDL.h>

namespace snake::client {
  /**
   * @brief Helper to make the SDL mockable.
   */
  struct SDL
  {
    SDL() = default;

    virtual ~SDL() = default;

    virtual int init(std::uint32_t features) = 0;

    virtual void quit() = 0;

    virtual char const * getError() = 0;

    virtual std::uint32_t wasInit(std::uint32_t features) = 0;

    virtual SDL_Window * createWindow(char const * title, int x, int y, int w, int h, std::uint32_t flags) = 0;

    virtual void destroyWindow(SDL_Window * window) = 0;

    virtual int setWindowDisplayMode(SDL_Window * window, SDL_DisplayMode const * mode) = 0;

    virtual int getWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode) = 0;

    virtual int pollEvent(SDL_Event * event) = 0;

    virtual int pushEvent(SDL_Event * event) = 0;

    virtual SDL_Surface * getWindowSurface(SDL_Window * window) = 0;

    virtual void freeSurface(SDL_Surface * surface) = 0;

    virtual int fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color) = 0;

    virtual std::uint32_t
    mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = 0;

    virtual int updateWindowSurface(SDL_Window * window) = 0;

    virtual std::string getBasePath() = 0;

    virtual std::string getPrefPath(char const * organizationName, char const * applicationName) = 0;
  };
}

#endif // SNAKE_SDL_HXX
