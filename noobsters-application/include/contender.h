#ifndef CONTENDER_H
#define CONTENDER_H
#include <cstdint>
#include <string>
#include <vector>

#include "core/time_unit.h"

namespace noobsters {
struct contender_data {
  std::string   m_contender_name;
  time_unit     m_best_lap;
};

struct lap_data {
  std::vector<time_unit>   m_sector_times{3};
  time_unit                           m_total_time;
};

struct stint_data {
  contender_data          m_contender;
  std::vector<lap_data>   m_laps;
  time_unit               m_total_time;
};

struct contending_team {
  std::uint64_t           m_position;
  std::int32_t            m_kart_number;
  std::string             m_nationality;
  lap_data                m_current_lap;
  std::vector<stint_data> m_stints;
  std::uint64_t           m_lap_count;
  std::uint64_t           m_pit_count;
  time_unit               m_pit_time;
  time_unit               m_gap_to_first;
  time_unit               m_gap_to_next;
};
}  // namespace noobsters
#endif  // COMPETER_H
