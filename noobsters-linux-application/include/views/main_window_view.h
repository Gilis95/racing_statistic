#ifndef MAIN_WINDOW_VIEW_H
#define MAIN_WINDOW_VIEW_H

namespace noobsters::linux_platform {
class main_window_view {
public:
  void set_racer_name(std::uint64_t sector_idx, time_unit time);
  void set_sector_time(std::uint64_t sector_idx, time_unit time);
  void set_kart_num(std::uint32_t kart_num);
  void set_pit_count(std::uint32_t pit_count);
  void set_pit_time(std::uint32_t pit_count, time_unit time);
  void set_penalty(std::uint32_t pit_count, time_unit time);
};
}

#endif //MAIN_WINDOW_VIEW_H
