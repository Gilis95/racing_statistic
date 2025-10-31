#include "core/noobsters_filesystem.h"

#include "core/noobsters_macros.h"

namespace noobsters {

filesystem::filesystem() = default;

filesystem& filesystem::instance() {
  static filesystem s_instance;
  return s_instance;
}

void filesystem::set_work_dir(std::filesystem::path work_dir) {
  m_work_dir = std::filesystem::canonical(work_dir);
}

std::filesystem::path filesystem::resolve_path(
    const std::filesystem::path& resource_path) {
  ReturnIf(resource_path.has_root_directory(), resource_path);

  ReturnIf(m_work_dir.empty(), std::filesystem::absolute(resource_path));
  // failsafe path has been already resolved or it has been provided as a full
  // path
  ReturnIf(resource_path.string().rfind(m_work_dir.string(), 0) == 0,
           std::filesystem::absolute(resource_path));

  return m_work_dir / resource_path;
}
}  // namespace noobsters