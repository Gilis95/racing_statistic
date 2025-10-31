#ifndef RACING_DATA_CHANGE_EVENT_H
#define RACING_DATA_CHANGE_EVENT_H
#include <cstdint>

namespace noobsters {
struct racing_entry_changed {
  std::uint64_t m_entry_idx;
};
}

#endif  // RACING_DATA_CHANGE_EVENT_H
