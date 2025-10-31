#ifndef LINUX_MACROS_H
#define LINUX_MACROS_H
#include <glib/gerror.h>

#include <expected>
#include <optional>

#include "core/noobsters_logger.h"
#include "core/noobsters_macros.h"

void inline check_error(const GError* maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_ERROR_TAG("UI", maybe_error->message);
}

void inline check_error(optional_const_ref<GError> maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_ERROR_TAG("UI", maybe_error->get().message);
}

template <typename T>
void check_critical_error(std::expected<T, ref<GError>> object_or_error) {
  ReturnIf(object_or_error.has_value());

  NOOBSTERS_CRITICAL_TAG("UI", object_or_error.error().get().message);
  CRASH;
}

void inline check_critical_error(optional_const_ref<GError> maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_CRITICAL_TAG("UI", maybe_error->get().message);
  CRASH;
}

void inline check_critical_error(GError* maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_CRITICAL_TAG("UI", maybe_error->message);
  CRASH;
}

#endif  // LINUX_MACROS_H
