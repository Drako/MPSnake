#include "native.hxx"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#else // !_WIN32

#include <climits>
#include <unistd.h>

#endif

namespace snake::client::native {
  std::filesystem::path getExePath()
  {
#ifdef _WIN32
    char buffer[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return buffer;
#else // !_WIN32
    char buffer[PATH_MAX] = {};
    auto const count = static_cast<std::size_t>(readlink("/proc/self/exe", buffer, PATH_MAX));
    return std::string{buffer, count > 0u ? count : 0u};
#endif
  }
}
