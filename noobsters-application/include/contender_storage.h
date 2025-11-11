
#ifndef CONTENDER_STORAGE_H
#define CONTENDER_STORAGE_H
#include "contender.h"
#include "ids.h"

namespace noobsters {
class contender_storage {
 private:
  contender_storage();
  ~contender_storage();

 public:
  static contender_storage& instance();

 public:
  optional_const_ref<noobsters::contending_team>& get(contender_id id) const;
  void set(contender_id id, noobsters::contending_team& team);

 private:
  std::vector<noobsters::contending_team> m_data;
};
}  // namespace noobsters
#endif  // CONTENDER_STORAGE_H
