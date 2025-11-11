#include "core/time_unit.h"

#include "core/noobsters_macros.h"

namespace {

const int k_hours_in_day = 24;
const int k_minutes_in_hour = 60;
const int k_seconds_in_minute = 60;
const int k_miliseconds_in_second = 1000;
const int k_microseconds_in_milisecond = 1000;
const int k_nanoseconds_in_microsecond = 1000;

std::uint64_t get_current_time();

noobsters::time_unit::value_type miliseconds_to_seconds(
    noobsters::time_unit::value_type time) {
  return time / k_miliseconds_in_second;
}

noobsters::time_unit::value_type miliseconds_to_minutes(
    noobsters::time_unit::value_type time) {
  return miliseconds_to_seconds(time) / k_seconds_in_minute;
}

noobsters::time_unit::value_type miliseconds_to_hours(
    noobsters::time_unit::value_type time) {
  return miliseconds_to_minutes(time) / k_minutes_in_hour;
}

noobsters::time_unit::value_type miliseconds_to_days(
    noobsters::time_unit::value_type time) {
  return miliseconds_to_hours(time) / k_hours_in_day;
}

#ifdef NOOBSTERS_LINUX
#include <time.h>

std::uint64_t get_current_time() {
  timespec spec{};
  clock_gettime(CLOCK_REALTIME, &spec);

  std::uint64_t epoch_nanosec = static_cast<std::uint64_t>(
      spec.tv_sec * k_miliseconds_in_second * k_microseconds_in_milisecond *
      k_nanoseconds_in_microsecond);

  epoch_nanosec += static_cast<std::uint64_t>(spec.tv_nsec);

  return epoch_nanosec /
         (k_nanoseconds_in_microsecond * k_microseconds_in_milisecond);
}
#endif

#ifdef NOOBSTERS_WINDOWS
#endif
}  // namespace
namespace noobsters {
time_unit::time_unit() : m_miliseconds(0) {}
time_unit::time_unit(std::uint64_t miliseconds) : m_miliseconds(miliseconds) {}

time_unit::time_unit(const time_unit& other)
    : m_miliseconds(other.m_miliseconds) {}
time_unit::time_unit(time_unit&& other) noexcept
    : m_miliseconds(other.m_miliseconds) {}

time_unit time_unit::from_current_time_in_miliseconds() {
  return time_unit{(get_current_time())};
}
time_unit time_unit::from_current_time_in_seconds() {
  return time_unit{miliseconds_to_seconds(get_current_time())};
}
time_unit time_unit::from_current_time_in_minutes() {
  return time_unit{miliseconds_to_minutes(get_current_time())};
}
time_unit time_unit::from_current_time_in_hours() {
  return time_unit{miliseconds_to_hours(get_current_time())};
}

time_unit::value_type time_unit::as_miliseconds() const {
  return m_miliseconds;
}
time_unit::value_type time_unit::as_seconds() const {
  return miliseconds_to_seconds(m_miliseconds);
}
time_unit::value_type time_unit::as_minutes() const {
  return miliseconds_to_minutes(m_miliseconds);
}

time_unit::value_type time_unit::as_hours() const {
  return miliseconds_to_hours(m_miliseconds);
}

time_unit::value_type time_unit::as_days() const {
  return miliseconds_to_days(m_miliseconds);
}

time_unit& time_unit::operator=(const time_unit& other) {
  if (this == &other) return *this;
  m_miliseconds = other.m_miliseconds;
  return *this;
}

time_unit& time_unit::operator=(time_unit&& other) noexcept {
  if (this == &other) return *this;
  m_miliseconds = other.m_miliseconds;
  return *this;
}

time_unit& time_unit::operator-=(time_unit other) {
  m_miliseconds -= other.m_miliseconds;

  return *this;
}
time_unit& time_unit::operator+=(time_unit other) {
  m_miliseconds += other.m_miliseconds;

  return *this;
}

time_unit time_unit::operator-(time_unit right) const {
  return time_unit(m_miliseconds - right.m_miliseconds);
}

time_unit time_unit::operator+(time_unit right) const {
  return time_unit(m_miliseconds + right.m_miliseconds);
}
}  // namespace noobsters