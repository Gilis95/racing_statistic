#ifndef NOOBSTERS_MACROS_H
#define NOOBSTERS_MACROS_H

#include <chrono>
#include <tuple>
#include <type_traits>

#include "core/noobsters_logger.h"

#ifdef NOOBSTERS_LINUX
#include <signal.h>
#define DEBUGBREAK() raise(SIGTRAP);
#elif NOOBSTERS_WINDOWS
#define DEBUGBREAK() __debug_breka
#else
#define DEBUGBREAK()
#endif

#ifdef ENABLE_ASSERTS
#define NOOBSTERSLOG_ERROR_AND_BREAK(...) \
  {                                       \
    NOOBSTERSERROR(__VA_ARGS__);          \
    DEBUGBREAK();                         \
  }
#else
#define NOOBSTERSLOG_ERROR_AND_BREAK(...)
#endif

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

// DO NOT delete the volatile keyword, otherwise compiler might delete the
// instruction
#define CRASH *(reinterpret_cast<volatile unsigned int*>(0)) = 0xDEAD

#define AssertLogIf(x, ...)                                               \
  {                                                                       \
    if ((x)) {                                                            \
      NOOBSTERSERROR("Assertion Failed: {0} {1} {2}", __FILE__, __LINE__, \
                     __FUNCTION__);                                       \
    }                                                                     \
  }
#define AssertLogUnless(x, ...)                                           \
  {                                                                       \
    if (!(x)) {                                                           \
      NOOBSTERSERROR("Assertion Failed: {0} {1} {2}", __FILE__, __LINE__, \
                     __FUNCTION__);                                       \
    }                                                                     \
  }

#define ReturnIf(x, ...)  \
  {                       \
    if (x) {              \
      return __VA_ARGS__; \
    }                     \
  }
#define ReturnUnless(x, ...) \
  {                          \
    if (!(x)) {              \
      return __VA_ARGS__;    \
    }                        \
  }

#define CrashIf(x, ...)                                                       \
  {                                                                           \
    if (x) {                                                                  \
      NOOBSTERSLOG_ERROR_AND_BREAK(                                           \
          "Forcefully crashing the program: {0} {1} {2}", __FILE__, __LINE__, \
          __FUNCTION__);                                                      \
      CRASH;                                                                  \
    }                                                                         \
  }

#define CrashUnless(x, ...)                                                   \
  {                                                                           \
    if (!(x)) {                                                               \
      NOOBSTERSLOG_ERROR_AND_BREAK(                                           \
          "Forcefully crashing the program: {0} {1} {2}", __FILE__, __LINE__, \
          __FUNCTION__);                                                      \
      CRASH;                                                                  \
    }                                                                         \
  }

#define AssertReturnIf(x, ...)                                                \
  {                                                                           \
    if (x) {                                                                  \
      NOOBSTERSLOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, \
                                   __LINE__, __FUNCTION__);                   \
      return __VA_ARGS__;                                                     \
    }                                                                         \
  }
#define AssertReturnUnless(x, ...)                                            \
  {                                                                           \
    if (!(x)) {                                                               \
      NOOBSTERSLOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, \
                                   __LINE__, __FUNCTION__);                   \
      return __VA_ARGS__;                                                     \
    }                                                                         \
  }

#define ContinueIf(x) \
  {                   \
    if (x) {          \
      continue;       \
    }                 \
  }
#define ContinueUnless(x) \
  {                       \
    if (!(x)) {           \
      continue;           \
    }                     \
  }

#define AssertContinueIf(x, ...)                                              \
  {                                                                           \
    if (x) {                                                                  \
      NOOBSTERSLOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, \
                                   __LINE__, __FUNCTION__);                   \
      continue;                                                               \
    }                                                                         \
  }
#define AssertContinueUnless(x, ...)                                          \
  {                                                                           \
    if (!(x)) {                                                               \
      NOOBSTERSLOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, \
                                   __LINE__, __FUNCTION__);                   \
      continue;                                                               \
    }                                                                         \
  }

template <typename T, typename... Ts>
constexpr bool contains = (std::is_same<T, Ts>{} || ...);

template <typename Subset, typename Set>
constexpr bool is_subset_of = false;

template <typename... Ts, typename... Us>
constexpr bool is_subset_of<std::tuple<Ts...>, std::tuple<Us...>> =
    (contains<Ts, Us...> && ...);

// helper type for the visitor
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#define DEFINE_ENUM_FLAG_OPERATIONS(T, base_type)      \
  inline T operator~(T a) {                            \
    return static_cast<T>(~static_cast<base_type>(a)); \
  }                                                    \
  inline T operator|(T a, T b) {                       \
    return static_cast<T>(static_cast<base_type>(a) |  \
                          static_cast<base_type>(b));  \
  }                                                    \
  inline T operator&(T a, T b) {                       \
    return static_cast<T>(static_cast<base_type>(a) &  \
                          static_cast<base_type>(b));  \
  }                                                    \
  inline T operator^(T a, T b) {                       \
    return static_cast<T>(static_cast<base_type>(a) ^  \
                          static_cast<base_type>(b));  \
  }                                                    \
  inline T& operator|=(T& a, T b) {                    \
    a = (a) | (b);                                     \
    return a;                                          \
  }                                                    \
  inline T& operator&=(T& a, T b) {                    \
    a = (a) & (b);                                     \
    return a;                                          \
  }                                                    \
  inline T& operator^=(T& a, T b) {                    \
    a = (a) ^ (b);                                     \
    return a;                                          \
  }

template <class child_class_type, class parent_class_type>
concept derived = std::is_base_of_v<parent_class_type, child_class_type>;

template <typename T>
using ref = std::reference_wrapper<T>;

template <typename T>
using const_ref = std::reference_wrapper<const T>;

template <typename T>
using optional_const_ref = std::optional<const_ref<T>>;

template <typename T>
using optional_ref = std::optional<ref<T>>;

#if defined(__GNUC__) || defined(__clang__)
#define BEGIN_IGNORE_WARNINGS                                                 \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wall\"") \
      _Pragma("GCC diagnostic ignored \"-Wextra\"") _Pragma(                 \
          "GCC diagnostic ignored \"-Wpedantic\"")                           \
          _Pragma("GCC diagnostic ignored \"-Wconversion\"") _Pragma(        \
              "GCC diagnostic ignored \"-Wmissing-declarations\"")           \
              _Pragma(                                                       \
                  "GCC diagnostic ignored \"-Wdeprecated-literal-operator\"") \
_Pragma(                                                       \
"GCC diagnostic ignored \"-Wold-style-cast\"")
#define END_IGNORE_WARNINGS _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
#define BEGIN_IGNORE_WARNINGS \
  __pragma(warning(push)) __pragma(warning(disable : 4996))
#define END_IGNORE_WARNINGS __pragma(warning(pop))
#else
#define BEGIN_IGNORE_WARNINGS
#define END_IGNORE_WARNINGS
#endif

#endif
