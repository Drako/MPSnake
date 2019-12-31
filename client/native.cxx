#include "native.hxx"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#elif defined(__APPLE__) || defined(__MACH__)

#include <climits>
#include <vector>
#include <mach-o/dyld.h>
#include <sys/param.h>

#else // linux/bsd/...

#include <climits>
#include <unistd.h>

#endif

namespace snake::client::native {
  std::filesystem::path getExePath()
  {
#ifdef _WIN32
    wchar_t buffer[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    return buffer;
#elif defined(__APPLE__) || defined(__MACH__)
    std::uint32_t bufferSize = MAXPATHLEN;
    char buffer[MAXPATHLEN] = {};
    if (_NSGetExecutablePath(buffer, &bufferSize) == -1)
    {
      std::vector<char> exactBuffer(bufferSize);
      _NSGetExecutablePath(exactBuffer.data(), &bufferSize);
      return { exactBuffer.data() };
    }
    return buffer;
#else // linux/bsd/...
    char buffer[PATH_MAX] = {};
    auto const count = static_cast<std::size_t>(readlink("/proc/self/exe", buffer, PATH_MAX));
    return std::string{buffer, count > 0u ? count : 0u};
#endif
  }
}
