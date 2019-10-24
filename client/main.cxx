#ifdef SNAKE_TESTING
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#else // !SNAKE_TESTING

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
  return 0;
}

#endif
