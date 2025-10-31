#include "core/resource_manager.h"

#include <gio/gio.h>

#include "core/noobsters_filesystem.h"

namespace noobsters::linux_platform {
/////////////////////////////////////////////////////////////////////////////////////////
resource_manager::resource_manager() = default;

/////////////////////////////////////////////////////////////////////////////////////////
/// Mayer's singleton
/////////////////////////////////////////////////////////////////////////////////////////
resource_manager& resource_manager::instance() {
  static resource_manager instance;
  return instance;
}

/////////////////////////////////////////////////////////////////////////////////////////
optional_const_ref<GError> resource_manager::load(
    resource_type type, std::string_view resource_path) {
  auto& fs = filesystem::instance();

  std::filesystem::path resource_dir_path = fs.resolve_path(resource_path);
  GError* error = nullptr;
  auto* const loaded_resources =
      g_resource_load(resource_dir_path.string().c_str(), &error);
  ReturnIf(error, *error);

  g_resources_register(loaded_resources);
  m_resources.emplace_back(std::make_pair(type, std::ref(*loaded_resources)));

  return std::nullopt;
}

/////////////////////////////////////////////////////////////////////////////////////////
optional_const_ref<GResource> resource_manager::find(resource_type type) const {
  auto found_resource_it = m_resources.find(type);
  ReturnIf(found_resource_it == m_resources.end(), std::nullopt);

  return found_resource_it->second;
}

/////////////////////////////////////////////////////////////////////////////////////////
optional_ref<GResource> resource_manager::find(resource_type type) {
  auto found_resource_it = m_resources.find(type);
  ReturnIf(found_resource_it == m_resources.end(), std::nullopt);

  return found_resource_it->second;
}

/////////////////////////////////////////////////////////////////////////////////////////
resource_manager::maybe_object resource_manager::find_object(
    resource_type type, std::string_view object_path) {
  static std::string s_error_message = "Failed to find resource";
  static GError s_error{0, G_FILE_ERROR_EXIST,
                        const_cast<gchar*>(s_error_message.c_str())};

  auto maybe_resource = find(type);
  ReturnUnless(maybe_resource.has_value(), std::unexpected(std::ref(s_error)));

  GError* error = nullptr;
  auto object =
      g_resource_lookup_data(&maybe_resource->get(), object_path.data(),
                             G_RESOURCE_LOOKUP_FLAGS_NONE, &error);
  ReturnIf(error, std::unexpected(std::ref(*error)));

  return object;
}

}  // namespace noobsters::linux_platform