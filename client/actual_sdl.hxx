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

    SDL_Surface * getWindowSurface(SDL_Window * window) override;

    void freeSurface(SDL_Surface * surface) override;

    int fillRect(SDL_Surface * destination, SDL_Rect const * rect, std::uint32_t color) override;

    std::uint32_t
    mapRGBA(SDL_PixelFormat const * format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) override;

    int updateWindowSurface(SDL_Window * window) override;

    std::string getBasePath() override;

    std::string getPrefPath(char const * organizationName, char const * applicationName) override;

    SDL_Surface *
    createRGBSurfaceWithFormat(std::uint32_t flags, int width, int height, int depth, std::uint32_t format) override;
  };
}

#endif // SNAKE_ACTUAL_SDL_HXX
