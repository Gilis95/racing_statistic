#ifndef MAIN_WINDOW_VIEW_H
#define MAIN_WINDOW_VIEW_H
#include <gtk/gtk.h>

#include "core/linux_macros.h"

namespace noobsters {
struct contending_team;
}

namespace noobsters::linux_platform {
class main_window_view {
 public:
  explicit main_window_view(GtkBuilder& builder);

 public:
  void add_row(const contending_team& contender);

 private:
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(position);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(kart_number);
  NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(nationality);
  NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(sector1);
  NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(sector2);
  NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(sector3);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(lap_total);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(lap_count);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(pit_count);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(pit_time);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(gap_to_first);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(gap_to_next);
  NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(contender_name);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(best_lap);
  NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(stint_total_time);

 private:
  GtkColumnView* m_view  = nullptr;
  GListStore*    m_model = nullptr;
};
}  // namespace noobsters::linux_platform

#endif  // MAIN_WINDOW_VIEW_H
