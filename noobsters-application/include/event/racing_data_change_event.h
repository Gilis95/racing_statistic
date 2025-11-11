#ifndef RACING_DATA_CHANGE_EVENT_H
#define RACING_DATA_CHANGE_EVENT_H
#include <cstdint>

#include "ids.h"

namespace noobsters {
struct base_contender_change_event {
  contender_id m_entry_idx;
};

struct contender_updated : public base_contender_change_event {
};

struct contender_created : public base_contender_change_event {
};

}

#endif  // RACING_DATA_CHANGE_EVENT_H
