#ifndef NOOBSTERS_LOGGER_H
#define NOOBSTERS_LOGGER_H

_Pragma("GCC diagnostic ignored \"-Wdeprecated-literal-operator\"")
#include <spdlog/spdlog.h>
    _Pragma("GCC diagnostic pop")

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    namespace noobsters {
  /////////////////////////////////////////////////////////////////////////////////////////
  class log {
   public:
    static void init();

    static spdlog::logger& get_logger() { return *s_logger; }

    template <typename... Args>
    static void trace_tag(std::string_view tag,
                          std::format_string<Args...> format, Args&&... args);
    template <typename... Args>
    static void debug_tag(std::string_view tag,
                          std::format_string<Args...> format, Args&&... args);
    template <typename... Args>
    static void info_tag(std::string_view tag,
                         std::format_string<Args...> format, Args&&... args);
    template <typename... Args>
    static void warn_tag(std::string_view tag,
                         std::format_string<Args...> format, Args&&... args);
    template <typename... Args>
    static void error_tag(std::string_view tag,
                          std::format_string<Args...> format, Args&&... args);
    template <typename... Args>
    static void fatal_tag(std::string_view tag,
                          std::format_string<Args...> format, Args&&... args);

    static void trace_tag(std::string_view tag, std::string_view message);
    static void debug_tag(std::string_view tag, std::string_view message);
    static void info_tag(std::string_view tag, std::string_view message);
    static void warn_tag(std::string_view tag, std::string_view message);
    static void error_tag(std::string_view tag, std::string_view message);
    static void fatal_tag(std::string_view tag, std::string_view message);

   private:
    log() = default;
    static std::shared_ptr<spdlog::logger> s_logger;
  };

  template <typename... Args>
  void log::trace_tag(std::string_view tag,
                      const std::format_string<Args...> format,
                      Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    trace_tag(tag, formatted);
  }

  template <typename... Args>
  void log::debug_tag(std::string_view tag,
                      const std::format_string<Args...> format,
                      Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    debug_tag(tag, formatted);
  }

  template <typename... Args>
  void log::warn_tag(std::string_view tag,
                     const std::format_string<Args...> format, Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    warn_tag(tag, formatted);
  }

  template <typename... Args>
  void log::info_tag(std::string_view tag,
                     const std::format_string<Args...> format, Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    info_tag(tag, formatted);
  }

  template <typename... Args>
  void log::error_tag(std::string_view tag,
                      const std::format_string<Args...> format,
                      Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    error_tag(tag, formatted);
  }

  template <typename... Args>
  void log::fatal_tag(std::string_view tag,
                      const std::format_string<Args...> format,
                      Args&&... args) {
    std::string formatted = std::format(format, std::forward<Args>(args)...);
    fatal_tag(tag, formatted);
  }

}  // namespace noobsters

#if defined(NOOBSTERS_ENABLE_LOG)
#define NOOBSTERS_TRACE(...) \
  noobsters::log::trace_tag("Unspecified", __VA_ARGS__)
#define NOOBSTERS_DEBUG(...) \
  noobsters::log::debug_tag("Unspecified", __VA_ARGS__)
#define NOOBSTERS_INFO(...) noobsters::log::info_tag("Unspecified", __VA_ARGS__)
#define NOOBSTERS_WARN(...) noobsters::log::warn_tag("Unspecified", __VA_ARGS__)
#define NOOBSTERS_ERROR(...) \
  noobsters::log::error_tag("Unspecified", __VA_ARGS__)
#define NOOBSTERS_CRITICAL(...) \
  noobsters::log::fatal_tag("Unspecified", __VA_ARGS__)

#define NOOBSTERS_TRACE_TAG(tag, ...) \
  noobsters::log::trace_tag(tag, __VA_ARGS__)
#define NOOBSTERS_DEBUG_TAG(tag, ...) \
  noobsters::log::debug_tag(tag, __VA_ARGS__)
#define NOOBSTERS_INFO_TAG(tag, ...) noobsters::log::info_tag(tag, __VA_ARGS__)
#define NOOBSTERS_WARN_TAG(tag, ...) noobsters::log::warn_tag(tag, __VA_ARGS__)
#define NOOBSTERS_ERROR_TAG(tag, ...) \
  noobsters::log::error_tag(tag, __VA_ARGS__)
#define NOOBSTERS_CRITICAL_TAG(tag, ...) \
  noobsters::log::fatal_tag(tag, __VA_ARGS__)

#else
#define NOOBSTERS_TRACE(...)
#define NOOBSTERS_INFO(...)
#define NOOBSTERS_WARN(...)
#define NOOBSTERS_ERROR(...)
#define NOOBSTERS_CRITICAL(...)
#define NOOBSTERS_TRACE_TAG(tag, ...)
#define NOOBSTERS_DEBUG_TAG(tag, ...)
#define NOOBSTERS_INFO_TAG(tag, ...)
#define NOOBSTERS_WARN_TAG(tag, ...)
#define NOOBSTERS_ERROR_TAG(tag, ...)
#define NOOBSTERS_CRITICAL_TAG(tag, ...)
#endif

#endif
