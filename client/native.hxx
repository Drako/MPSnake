#pragma once

#ifndef SNAKE_NATIVE_HXX
#define SNAKE_NATIVE_HXX

#include <filesystem>

namespace snake::client::native {
  std::filesystem::path getExePath();
}

#endif // SNAKE_NATIVE_HXX
