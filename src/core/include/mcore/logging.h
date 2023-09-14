
#ifndef MXC_CORE_LOGGING_H
#define MXC_CORE_LOGGING_H

#include <cstdint>

#if defined(MXC_LOGLEVEL_INFO)
#define MXC_INFO(message, ...) ::mxc::core::logOutput(::mxc::LogLevel::info, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
#define MXC_INFO(...)
#endif

#if defined(MXC_LOGLEVEL_DEBUG)
#define MXC_DEBUG(message, ...)                                                                                        \
    ::mxc::core::logOutput(::mxc::LogLevel::debug, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
#define MXC_DEBUG(...)
#endif

#if defined(MXC_LOGLEVEL_WARN)
#define MXC_WARN(message, ...) ::mxc::core::logOutput(::mxc::LogLevel::warn, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
#define MXC_WARN(...)
#endif

#if defined(MXC_LOGLEVEL_ERROR)
#define MXC_ERROR(message, ...)                                                                                        \
    ::mxc::core::logOutput(::mxc::LogLevel::error, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
#define MXC_ERROR(...)
#endif

#if defined(MXC_LOGLEVEL_TRACE)
#define MXC_TRACE(message, ...)                                                                                        \
    ::mxc::core::logOutput(::mxc::LogLevel::trace, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
#define MXC_TRACE(...)
#endif

#if defined(_DEBUG) || defined(MXC_DEBUG)
#define MXC_ASSERT(condition, message, ...)                                                                            \
    ::mxc::core::assertCondition(__FILE__, __LINE__, (condition), (message), ##__VA_ARGS__)
#else
#define MXC_ASSERT(...)
#endif

namespace mxc::core
{
enum class LogLevel
{
    info,
    debug,
    warn,
    error,
    trace
};

// taken from kohi game engine https://github.com/travisvroman/kohi
// TODO find a way to make it work with fmt::print, so that I can use its format style instead of C format specifiers
auto stringFormat_v(char *dest, char const *format, void *va_listp) -> int32_t;

auto logOutput(LogLevel level, char const *file, int32_t const line, char const *message, ...) -> void;

auto assertCondition(char const *file, int32_t const line, bool condition, char const *message, ...) -> void;
} // namespace mxc::core

namespace mcore = mxc::core;

#endif // MXC_CORE_LOGGING_H
