#ifndef NOOBSTERS_FILESYSTEM_H
#define NOOBSTERS_FILESYSTEM_H

#include <filesystem>

#include "non_copyable.h"

namespace noobsters {
class filesystem : public non_copyable {
 private:
  filesystem();

 public:
  static filesystem& instance();

 public:
  void set_work_dir(std::filesystem::path work_dir);

  std::filesystem::path resolve_path(
      const std::filesystem::path& resource_path);

 private:
  std::filesystem::path m_work_dir;
};
}  // namespace noobsters
#endif  // NOOBSTERS_FILESYSTEM_H
