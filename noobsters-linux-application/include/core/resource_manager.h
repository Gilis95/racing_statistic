#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <gio/gio.h>

#include <cstdint>
#include <expected>
#include <string>

#include "core/non_copyable.h"
#include "core/noobsters_macros.h"
#include "core/vector_map.h"

namespace noobsters::linux_platform {
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
enum class resource_type : uint8_t {
  MAIN_MENUS = 0,
  MAIN_STYLES,
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class resource_manager : public non_copyable {
 public:
  using maybe_object = std::expected<GBytes*, ref<GError>>;

 private:
  resource_manager();

 public:
  [[nodiscard]] static resource_manager& instance();

 public:
  optional_const_ref<GError> load(resource_type type,
                                  std::string_view resource_path);
  void unload(resource_type type);

 public:
  [[nodiscard]] optional_const_ref<GResource> find(resource_type type) const;
  [[nodiscard]] optional_ref<GResource> find(resource_type type);

  [[nodiscard]] maybe_object find_object(resource_type type,
                                         std::string_view object_path);

 private:
  vector_map<resource_type, std::reference_wrapper<GResource>> m_resources;
};
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
}  // namespace noobsters::linux_platform
#endif  // RESOURCE_MANAGER_H
